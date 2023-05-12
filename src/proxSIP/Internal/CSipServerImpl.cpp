#include "Internal/CSipServerImpl.h"
#include "Internal/CSIPResponseImpl.h"

CSipServerImpl::CSipServerImpl()
    : m_pSender(nullptr)
{

}

void CSipServerImpl::SetSender(ISipMessageSender* pSender)
{
    m_pSender = pSender;
}

void CSipServerImpl::OnRequest(const ISIPRequest& Request)
{
    auto const eMethod = Request.Method();

    if (eMethod == ESipMethod::REGISTER)
    {
        CSIPResponseImpl Response;
        Response.Destination().Assign(Request.Source());
        Response.Source().Assign(Request.Destination());
        Response.Version(Request.Version());

        Response.Status(ESipStatusCode::Ok);

        auto& respFields = Response.Fields();
        for (auto& it = Request.Fields().StartEnumerator(); it; ++it)
            respFields.Insert(it->Key(), it->Value());

        m_pSender->SendMessage(Response);
    }
    else
    {

    }
}

void CSipServerImpl::OnResponse(const ISIPResponse& Request)
{

}