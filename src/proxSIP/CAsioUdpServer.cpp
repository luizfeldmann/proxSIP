#include "CAsioUdpServer.h"
#include "Internal/CAsioUdpServerImpl.h"

/* CAsioUdpServer */

CAsioUdpServer::CAsioUdpServer()
    : m_pImpl(new CAsioUdpServerImpl)
{

}

CAsioUdpServer::~CAsioUdpServer()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

IEndpoint& CAsioUdpServer::LocalEndpoint()
{
    return m_pImpl->LocalEndpoint();
}

const IEndpoint& CAsioUdpServer::LocalEndpoint() const
{
    return m_pImpl->LocalEndpoint();
}

void CAsioUdpServer::SetHandler(IUdpMessageHandler* pHandler)
{
    m_pImpl->SetHandler(pHandler);
}

void CAsioUdpServer::SendMessage(const char* pData, size_t uSize, const IEndpoint& Dst)
{
    m_pImpl->SendMessage(pData, uSize, Dst);
}

bool CAsioUdpServer::Start()
{
    return m_pImpl->Start();
}

bool CAsioUdpServer::Stop()
{
    return m_pImpl->Stop();
}

void CAsioUdpServer::Poll()
{
    return m_pImpl->Poll();
}