#include "Internal/CSipServerImpl.h"
#include "Internal/CSIPResponseImpl.h"
#include "Internal/CAuthDigestImpl.h"
#include "Internal/CSipViaImpl.h"
#include "ESipParameter.h"
#include <map>

/* Util */

static void ReturnToSender(const ISIPMessage& From, ISIPMessage& To)
{
    To.Assign(From);

    // Invert source and destination
    To.Destination().Assign(From.Source());
    To.Source().Assign(From.Destination());
}

static void ChangeContact(ISIPMessage& Message, const IEndpoint& Server)
{
    for (auto& Contact = Message.Contact().iterate(); Contact; ++Contact)
    {
        auto& URI = Contact->URI();
        URI.Host(Server.Address());
        URI.Port(Server.Port());
    }
}

static std::map<std::string, std::string> m_changedVias;

static void RestoreVia(ISIPMessage& Message)
{
    for (auto& Via = Message.Via().iterate(); Via; ++Via)
    {
        const char* branch = Via->Parameters().Find(SipGetParamStr(ESipParameter::branch));
        if (branch)
        {
            auto itFind = m_changedVias.find(branch);
            if (itFind != m_changedVias.cend())
            {
                Via->URI(itFind->second.c_str());
            }
        }
    }
}

static void RewriteVia(ISIPMessage& Message, const IEndpoint& Server)
{
    for (auto& Via = Message.Via().iterate(); Via; ++Via)
    {
        const char* branch = Via->Parameters().Find(SipGetParamStr(ESipParameter::branch));
        if (branch)
        {
            m_changedVias[branch] = Via->URI();
        }

        std::string sURI = std::string(Server.Address()) + ":" + std::to_string(Server.Port());
        Via->URI(sURI.c_str());
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

    if (m_pRegistry)
    {
        Request.URI().KeepComponents(ESipURIComponents::PUH);
        sLocation = m_pRegistry->Locate(Request.URI().c_str());
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
    RewriteVia(Request, Request.Destination());

    // Retransmit
    Proxy(Request, sLocation);
}

void CSipServerImpl::Ack(ISIPRequest& Request)
{
    Request.URI().KeepComponents(ESipURIComponents::PUH);

    const char* sLocation = m_pRegistry->Locate(Request.URI().c_str());
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

    // Validate message
    if (Response.Contact().empty() || Response.Via().empty())
    {
        Response.Status(ESipStatusCode::BadRequest);
        return;
    }

    auto& Contact = Response.Contact().front();
    auto& Via = Response.Via().front();

    // Update the received address in the VIA
    Via.Parameters().Insert(SipGetParamStr(ESipParameter::received), Response.Destination().Address());

    // Get the expiration
    unsigned int uExpires = 3600;
    const char *sExpires = Contact.Parameters().Find(SipGetParamStr(ESipParameter::expires));
    if (sExpires)
    {
        try {
            uExpires = std::stoi(sExpires);
        }
        catch (...) {}
    }

    // Perform the registration
    Response.To().URI().KeepComponents(ESipURIComponents::PUH);
    m_pRegistry->Register(Response.To().URI().c_str(), Via.URI(), uExpires);

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
    RestoreVia(Response);

    auto& Via = Response.Via().front();

    const auto eStatus = Response.Status();
    if (eStatus == ESipStatusCode::Ok)
    {
        ChangeContact(Response, Response.Destination());
    }

    Proxy(Response, Via.URI());
}