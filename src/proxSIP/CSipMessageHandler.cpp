#include "CSipMessageHandler.h"
#include "CSipParser.h"
#include "CSIPRequest.h"
#include "CSIPResponse.h"
#include <boost/log/trivial.hpp>

CSipMessageHandler::CSipMessageHandler()
    : CSipMessageHandler(nullptr, nullptr)
{

}

CSipMessageHandler::CSipMessageHandler(ISipRequestHandler* pRequestHandler, ISipResponseHandler* pResponseHandler)
    : m_pRequestHandler(pRequestHandler)
    , m_pResponseHandler(pResponseHandler)
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

ISipRequestHandler* CSipMessageHandler::GetRequestHandler()
{
    return m_pRequestHandler;
}

ISipResponseHandler* CSipMessageHandler::GetResponseHandler()
{
    return m_pResponseHandler;
}

void CSipMessageHandler::OnMessage(const char* pData, size_t uSize, const char* szFromAddr, unsigned short usFromPort)
{
    bool bParsed = false;

    // Try parse as a request
    if (m_pRequestHandler)
    {
        CSIPRequest Request;

        if (CSipParser::ParseRequest(pData, uSize, Request))
        {
            bParsed = true;
            m_pRequestHandler->OnRequest(Request);
        }
    }

    // Try parse as a response
    if (m_pResponseHandler && !bParsed)
    {
        CSIPResponse Response;

        if (CSipParser::ParseResponse(pData, uSize, Response))
        {
            bParsed = true;
            m_pResponseHandler->OnResponse(Response);
        }
    }

    // Report invalid
    if (!bParsed)
    {
        BOOST_LOG_TRIVIAL(error) << "UDP message is not compliant to SIP";
    }
}