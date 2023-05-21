#include "CCallSession.h"

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

}