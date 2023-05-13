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

void CSipServerImpl::OnRequest(ISIPRequest& Request)
{
    // If a validator is provided, authenticate the message
    if (m_pAuth)
    {
        CAuthDigestImpl Digest;

        // TODO: Read digest from request

        ESipStatusCode eStatus = m_pAuth->ValidateAuth(Digest);

        if (eStatus != ESipStatusCode::Ok)
        {
            // Bad auth, must return message to sender
            CSIPResponseImpl Response;

            ReturnToSender(Request, Response);
            Response.Status(eStatus);

            // TODO: Write updated digest into Response

            m_pSender->SendMessage(Response);
            return;
        }
    }

    // Handle the special registration request
    auto const eMethod = Request.Method();

    if (eMethod == ESipMethod::REGISTER)
    {
        ESipStatusCode eStatus = ESipStatusCode::Ok;
        CSIPResponseImpl Response;
        ReturnToSender(Request, Response);

        // Read contact to be registered and the Via
        auto& RespFields = Response.Fields();
        TFieldAccessor<CSipContactImpl, decltype(RespFields)> Contact(ESipField::To, RespFields);
        TFieldAccessor<CSipViaImpl, decltype(RespFields)> Via(ESipField::Via, RespFields);

        if (!Contact.Read() || !Via.Read())
            eStatus = ESipStatusCode::BadRequest;
        else
        {
            // Update the received address in the VIA
            Via->Parameters().Insert(SipGetParamStr(ESipParameter::received), Request.Source().Address());
            Via.Write();

            if (!m_pRegistry)
                eStatus = ESipStatusCode::NotImplemented;
            else
                m_pRegistry->Register(Request.URI(), *Contact, *Via);
        }

        // Send back the filled response
        Response.Status(eStatus);
        m_pSender->SendMessage(Response);
        return;
    }

    // Proxy: forward the request to the correct UA
    auto& ReqFields = Request.Fields();
    
    // Figure out where to redirect
    TFieldAccessor<CSipViaImpl, decltype(ReqFields)> RequestVia(ESipField::Via, ReqFields);
    TFieldAccessor<CSipContactImpl, decltype(ReqFields)> RequestTo(ESipField::To, ReqFields);
    
    if (!RequestTo.Read() || !RequestVia.Read())
    {
        return;
    }

    CSipViaImpl RedirectVia;
    CEndpointImpl RedirectEdp;
    if (!m_pRegistry || !m_pRegistry->Locate(Request.URI(), *RequestTo, RedirectVia))
    {
        return;
    }

    // Find endpoint of redirect target
    {
        const std::string sUri = RedirectVia.URI();
        const size_t nSep = sUri.find(':');

        RedirectEdp.Address(sUri.substr(0, nSep).c_str());

        unsigned short usPort = 5060;
        if (nSep != std::string::npos)
        {
            sscanf(sUri.substr(nSep+1).c_str(), "%hu", &usPort);
        }

        RedirectEdp.Port(usPort);
    }

    Request.Source().Assign(Request.Destination());
    Request.Destination().Assign(RedirectEdp);

    m_pSender->SendMessage(Request);
}

void CSipServerImpl::OnResponse(ISIPResponse& Response)
{

}