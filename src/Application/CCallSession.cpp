#include "CCallSession.h"
#include <boost/log/trivial.hpp>

CCallSession::CCallSession()
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

void CCallSession::OnMessage(const char* pData, size_t uSize)
{
    if (!m_msgRtp.Parse(pData, uSize))
        return; // Unable to parse RTP

    if (m_msgRtp.PayloadType() != 101)
        return; // Wrong payload type

    if (!m_msgRtp.Marker())
        return; // No marker - not 'start' of DTMF

    auto& Payload = m_msgRtp.Payload();

    if (!m_evtDtmf.Parse(Payload.cbegin(), Payload.size()))
        return; // Unable to parse DTMF

    if (m_evtDtmf.End())
        return; // Ignore end

    OnDTMF(m_evtDtmf.EventCode());
}

void CCallSession::OnDTMF(EPhoneEventCode eCode)
{
    BOOST_LOG_TRIVIAL(info) << "DTMF: " << (unsigned int)eCode;
}