#include "Internal/CSipServerImpl.h"
#include "Internal/CSIPResponseImpl.h"
#include "Internal/CAuthDigestImpl.h"
#include "Internal/CSipViaImpl.h"
#include "Internal/CSipContactImpl.h"
#include "ESipParameter.h"
#include "TFieldAccessor.h"

/* Util */

static void CopyMessage(const ISIPMessage& From, ISIPMessage& To)
{
    // Copy version
    To.Version(From.Version());

    // Copy fields
    auto& toFields = To.Fields();

    for (auto& it = From.Fields().StartEnumerator(); it; ++it)
        toFields.Insert(it->Key(), it->Value());

    // Copy body content
    const auto& fromBody = From.Content();

    if (fromBody.size())
    {
        To.Content().write(fromBody.cbegin(), fromBody.size());
    }
}

static void ReturnToSender(const ISIPMessage& From, ISIPMessage& To)
{
    CopyMessage(From, To);

    // Invert source and destination
    To.Destination().Assign(From.Source());
    To.Source().Assign(From.Destination());
}

static void ChangeContact(ISIPMessage& Message, const IEndpoint& Server)
{
    auto Contact = CreateFieldAccessor<CSipContactImpl>(ESipField::Contact, Message.Fields());
    if (Contact.Read())
    {
        std::string sURI = Contact->URI();
        const auto p1 = sURI.find_first_of(":") + 1;
        const auto p2 = sURI.find_first_of("@");

        const std::string sUserName = sURI.substr(p1, p2 - p1);
        sURI = "sip:" + sUserName + "@" + std::string(Server.Address()) + ":" + std::to_string(Server.Port()) + ";transport=udp";
        Contact->URI(sURI.c_str());

        Contact.Write();
    }
}

/* CSipServerImpl */

CSipServerImpl::CSipServerImpl()
    : m_pSender(nullptr)
    , m_pAuth(nullptr)
    , m_pRegistry(nullptr)
{

}

void CSipServerImpl::SetAuth(IAuthValidator* pAuth)
{
    m_pAuth = pAuth;
}

void CSipServerImpl::SetSender(ISipMessageSender* pSender)
{
    m_pSender = pSender;
}

void CSipServerImpl::SetRegistry(ISipRegistry* pReg)
{
    m_pRegistry = pReg;
}

void CSipServerImpl::Proxy(ISIPMessage& Message, const char* sLocation)
{
    CEndpointImpl RedirectEdp;
    {
        const std::string sUri = sLocation;
        const size_t nSep = sUri.find(':');

        RedirectEdp.Address(sUri.substr(0, nSep).c_str());

        unsigned short usPort = 5060;
        if (nSep != std::string::npos)
        {
            sscanf(sUri.substr(nSep + 1).c_str(), "%hu", &usPort);
        }

        RedirectEdp.Port(usPort);
    }

    Message.Source().Assign(Message.Destination());
    Message.Destination().Assign(RedirectEdp);
    m_pSender->SendMessage(Message);
}

void CSipServerImpl::Invite(ISIPRequest& Request)
{
    // Try to find the user where to send the request to
    const char* sLocation = nullptr;
    const char* const sCallee = Request.URI();

    if (m_pRegistry)
    {
        sLocation = m_pRegistry->Locate(sCallee);
    }

    // Error if user does not exist
    if (!sLocation)
    {
        // Cannot locate user
        CSIPResponseImpl Response;

        ReturnToSender(Request, Response);

        if (m_pRegistry)
            Response.Status(ESipStatusCode::NotFound);
        else
            Response.Status(ESipStatusCode::NotImplemented);

        m_pSender->SendMessage(Response);
        return;
    }

    ChangeContact(Request, Request.Destination());

    // Retransmit
    Proxy(Request, sLocation);
}

void CSipServerImpl::Ack(ISIPRequest& Request)
{
    std::string sUri = Request.URI();
    sUri = sUri.substr(0, sUri.find_last_of(':'));

    const char* sLocation = m_pRegistry->Locate(sUri.c_str());
    if (!sLocation)
        return;

    Proxy(Request, sLocation);
}

void CSipServerImpl::Bye(ISIPRequest& Request)
{
    Ack(Request);
}

bool CSipServerImpl::Authenticate(ISIPRequest& Request)
{
    // If no validator is provided, skip the authentication
    bool bStatus = true;

    // If a validator is provided, authenticate the message
    if (m_pAuth)
    {
        CAuthDigestImpl Digest;

        // TODO: Read digest from request

        // Ask the validator to check/update the digest
        ESipStatusCode eStatus = m_pAuth->ValidateAuth(Digest);

        if (eStatus != ESipStatusCode::Ok)
        {
            // Bad auth, must return message to sender
            CSIPResponseImpl Response;

            ReturnToSender(Request, Response);
            Response.Status(eStatus);

            // TODO: Write updated digest into Response

            m_pSender->SendMessage(Response);
            bStatus = false;
        }
    }

    return bStatus;
}

void CSipServerImpl::DoRegister(ISIPResponse& Response)
{
    // Check we are capable of registering
    if (!m_pRegistry)
    {
        Response.Status(ESipStatusCode::NotImplemented);
        return;
    }

    // Read relevant fields
    auto& Fields = Response.Fields();
    auto Contact = CreateFieldAccessor<CSipContactImpl>(ESipField::Contact, Fields);
    auto To = CreateFieldAccessor<CSipContactImpl>(ESipField::To, Fields);
    auto Via = CreateFieldAccessor<CSipViaImpl>(ESipField::Via, Fields);

    // Validate message
    if (!Contact.Read() || !To.Read() || !Via.Read())
    {
        Response.Status(ESipStatusCode::BadRequest);
        return;
    }

    // Update the received address in the VIA
    Via->Parameters().Insert(SipGetParamStr(ESipParameter::received), Response.Destination().Address());
    Via.Write();

    // Get the expiration
    unsigned int uExpires = 3600;
    const char *sExpires = Contact->Parameters().Find(SipGetParamStr(ESipParameter::expires));
    if (sExpires)
    {
        try {
            uExpires = std::stoi(sExpires);
        }
        catch (...) {}
    }

    // Perform the registration
    m_pRegistry->Register(To->URI(), Via->URI(), uExpires);

    Response.Status(ESipStatusCode::Ok);
    return;
}

void CSipServerImpl::Register(ISIPRequest& Request)
{
    CSIPResponseImpl Response;
    ReturnToSender(Request, Response);

    DoRegister(Response);

    m_pSender->SendMessage(Response);
}

void CSipServerImpl::OnRequest(ISIPRequest& Request)
{
    // Try to authenticate the request
    if (!Authenticate(Request))
        return;

    // Method-specific handling
    auto const eMethod = Request.Method();
    switch (eMethod)
    {
    case ESipMethod::REGISTER:
        Register(Request);
        break;

    case ESipMethod::INVITE:
        Invite(Request);
        break;

    case ESipMethod::ACK:
        Ack(Request);
        break;

    case ESipMethod::BYE:
        Bye(Request);
        break;

    default:
        break;
    }
}

void CSipServerImpl::OnResponse(ISIPResponse& Response)
{
    auto Via = CreateFieldAccessor<CSipViaImpl>(ESipField::Via, Response.Fields());
    Via.Read();

    const auto eStatus = Response.Status();
    if (eStatus == ESipStatusCode::Ok)
    {
        ChangeContact(Response, Response.Destination());
    }

    Proxy(Response, Via->URI());
}