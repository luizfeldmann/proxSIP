#include "Internal/CSipServerImpl.h"
#include "Internal/CSIPResponseImpl.h"
#include "Internal/CAuthDigestImpl.h"

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

void CSipServerImpl::OnRequest(const ISIPRequest& Request)
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
        // TODO: add contact to the registry

        CSIPResponseImpl Response;

        ReturnToSender(Request, Response);
        Response.Status(ESipStatusCode::Ok);

        m_pSender->SendMessage(Response);
        return;
    }

    // Proxy: forward the request to the correct UA
    
    // TODO: find UA
    //       forward the Request
}

void CSipServerImpl::OnResponse(const ISIPResponse& Response)
{

}