#include "CSipMessageHandler.h"
#include "TBuffer.h"
#include "CSIPRequest.h"
#include "CSIPResponse.h"
#include <vector>
#include <boost/log/trivial.hpp>

CSipMessageHandler::CSipMessageHandler()
    : CSipMessageHandler(nullptr, nullptr, nullptr)
{

}

CSipMessageHandler::CSipMessageHandler(ISipRequestHandler* pRequestHandler, ISipResponseHandler* pResponseHandler, IUdpMessageSender* pSender)
    : m_pRequestHandler(pRequestHandler)
    , m_pResponseHandler(pResponseHandler)
    , m_pMessageSender(pSender)
{

}

void CSipMessageHandler::SetHandler(ISipRequestHandler* pHandler)
{
    m_pRequestHandler = pHandler;
}

void CSipMessageHandler::SetHandler(ISipResponseHandler* pHandler)
{
    m_pResponseHandler = pHandler;
}

void CSipMessageHandler::SetSender(IUdpMessageSender* pSender)
{
    m_pMessageSender = pSender;
}

ISipRequestHandler* CSipMessageHandler::GetRequestHandler()
{
    return m_pRequestHandler;
}

ISipResponseHandler* CSipMessageHandler::GetResponseHandler()
{
    return m_pResponseHandler;
}

IUdpMessageSender* CSipMessageHandler::GetSender()
{
    return m_pMessageSender;
}

void CSipMessageHandler::OnMessage(const char* pData, size_t uSize, const IEndpoint& Src, const IEndpoint& Dst)
{
    bool bParsed = false;

    // Try parse as a request
    if (m_pRequestHandler)
    {
        CSIPRequest Request;

        if (Request.Parse(pData, uSize))
        {
            bParsed = true;
            Request.Source().Assign(Src);
            Request.Destination().Assign(Dst);

            m_pRequestHandler->OnRequest(Request);
        }
    }

    // Try parse as a response
    if (m_pResponseHandler && !bParsed)
    {
        CSIPResponse Response;

        if (Response.Parse(pData, uSize))
        {
            bParsed = true;
            Response.Source().Assign(Src);
            Response.Destination().Assign(Dst);

            m_pResponseHandler->OnResponse(Response);
        }
    }

    // Report invalid
    if (!bParsed)
    {
        BOOST_LOG_TRIVIAL(error) << "UDP message is not compliant to SIP";
    }
}

void CSipMessageHandler::SendMessage(const ISIPMessage& Message)
{
    if (m_pMessageSender)
    {
        TBuffer<std::vector<char>> Buffer;
        Message.Serialize(Buffer);

        m_pMessageSender->SendMessage(Buffer.cbegin(), Buffer.size(), Message.Destination());
    }
}