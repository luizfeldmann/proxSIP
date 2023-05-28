#include "CCallSniffer.h"
#include <proxSIP/CSdpMessage.h>
#include <proxSIP/ESipField.h>
#include <boost/log/trivial.hpp>
#include <string>

CCallSniffer::CCallSniffer()
    : m_pRequestHandler(nullptr)
    , m_pResponseHandler(nullptr)
    , m_pDtmfHandler(nullptr)
{

}

void CCallSniffer::SetHandler(ISipRequestHandler* pHandler)
{
    m_pRequestHandler = pHandler;
}

void CCallSniffer::SetHandler(ISipResponseHandler* pHandler)
{
    m_pResponseHandler = pHandler;
}

void CCallSniffer::SetHandler(IEvtHandlerDTMF* pHandler)
{
    m_pDtmfHandler = pHandler;
}

void CCallSniffer::Poll()
{
    for (auto& Call : m_mSessions)
        Call.second->Poll();
}

void CCallSniffer::RewriteSDP(ISIPMessage& Message, CCallSession& Call)
{
    // Check the SDP is contained in the message
    if (0 == strcmp("application/sdp", Message.ContentType()))
    {
        // Parse the body into the structured SDP
        auto& Body = Message.Content();

        CSdpMessage SDP;
   
        if (SDP.Parse(Body.cbegin(), Body.size()))
        {
            // Modify the session description
            RewriteSDP(Message, SDP, Call);

            // Write back into the message body
            Body.clear();
            SDP.Serialize(Body);
            Message.ContentLength(Body.size());
        }
        else
        {
            BOOST_LOG_TRIVIAL(error) << "Unable to parse SDP";
        }
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "Body content-type is not SDP";
    }
}

void CCallSniffer::RewriteSDP(ISIPMessage& Message, ISdpMessage& SDP, CCallSession& Call)
{
    const char* const sLocalAddr = Message.Destination().Address();

    // Replace connection address for local and save remote
    if (SDP.Connection().empty())
    {
        BOOST_LOG_TRIVIAL(error) << "No connection info in SDP";
        return;
    }

    auto& Conn = SDP.Connection().front();

    std::string sRemoteAddr = Conn.Address();
    Conn.Address(sLocalAddr);

    // Replace origin address for local
    SDP.Origin().Address(sLocalAddr);
    
    // Find media port
    if (SDP.Media().empty())
    {
        BOOST_LOG_TRIVIAL(error) << "No media info in SDP";
        return;
    }

    auto& Media = SDP.Media().front();

    const unsigned short usRemotePort = Media.Port();

    // Create the proxy
    const unsigned short usLocalPort = Call.AddProxy(sLocalAddr, sRemoteAddr.c_str(), usRemotePort);

    // Update the port number in the SDP
    Media.Port(usLocalPort);
}

void CCallSniffer::OnRequest(ISIPRequest& Request)
{
    if (Request.Method() == ESipMethod::INVITE)
    {
        const char* pCallID = Request.CallID();

        if (pCallID)
        {
            BOOST_LOG_TRIVIAL(info) << "New call: " << pCallID;

            // Create a new call session
            auto itInsert = m_mSessions.insert({ pCallID, std::make_unique<CCallSession>() });
            CCallSession& Call = *itInsert.first->second;
            Call.SetHandler(m_pDtmfHandler);
            RewriteSDP(Request, Call);
        }
    }
    else if (Request.Method() == ESipMethod::BYE)
    {
        const char* pCallID = Request.CallID();

        // Delete the call session
        if (pCallID)
        {
            BOOST_LOG_TRIVIAL(info) << "End of call: " << pCallID;
            m_mSessions.erase(pCallID);
        }
    }

    if (m_pRequestHandler)
        m_pRequestHandler->OnRequest(Request);
}

void CCallSniffer::OnResponse(ISIPResponse& Response)
{
    if (Response.Status() == ESipStatusCode::Ok)
    {
        const char* pCallID = Response.CallID();

        if (pCallID)
        {
            auto itFind = m_mSessions.find(pCallID);
            if (m_mSessions.end() == itFind)
            {
                BOOST_LOG_TRIVIAL(error) << "Cannot find call ID";
            }
            else
            {
                RewriteSDP(Response, *itFind->second);
            }
        }
    }

    if (m_pResponseHandler)
        m_pResponseHandler->OnResponse(Response);
}
