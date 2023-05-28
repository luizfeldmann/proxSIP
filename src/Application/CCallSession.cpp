#include "CCallSession.h"
#include <boost/log/trivial.hpp>

CCallSession::CCallSession()
    : m_pEvtHandler(nullptr)
{
}

void CCallSession::Poll()
{
    for (auto& prx : m_arrPrx)
    {
        if (prx.has_value())
            prx->Poll();
    }
}

unsigned short CCallSession::AddProxy(const char* sLocalAddr, const char* sRemoteAddr, unsigned short uRemotePort)
{
    unsigned short uLocalPort = 0;

    for (auto& prx : m_arrPrx)
    {
        // Skip filled slots
        if (prx.has_value())
            continue;

        // Add to the first free slot
        prx.emplace(sLocalAddr, sRemoteAddr, uRemotePort);
        prx->SetHandler(this);
        uLocalPort = prx->LocalPort();

        break;
    }

    return uLocalPort;
}

void CCallSession::SetHandler(IEvtHandlerDTMF* pHandler)
{
    m_pEvtHandler = pHandler;
}

void CCallSession::OnMessage(const char* pData, size_t uSize)
{
    if (!m_msgRtp.Parse(pData, uSize))
        return; // Unable to parse RTP

    if (m_msgRtp.PayloadType() != 101)
        return; // Wrong payload type

    auto& Payload = m_msgRtp.Payload();

    if (!m_evtDtmf.Parse(Payload.cbegin(), Payload.size()))
        return; // Unable to parse DTMF

    // Send to handler
    if (m_pEvtHandler)
        m_pEvtHandler->OnEvent(m_evtDtmf);
}