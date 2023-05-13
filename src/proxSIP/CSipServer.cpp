#include "CSipServer.h"
#include "Internal/CSipServerImpl.h"

/* CSipServerImpl */

/* CSipServer */

CSipServer::CSipServer()
    : m_pImpl(new CSipServerImpl)
{

}

CSipServer::~CSipServer()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

void CSipServer::SetAuth(IAuthValidator* pAuth)
{
    m_pImpl->SetAuth(pAuth);
}

void CSipServer::SetSender(ISipMessageSender* pSender)
{
    m_pImpl->SetSender(pSender);
}

void CSipServer::SetRegistry(ISipRegistry* pReg)
{
    m_pImpl->SetRegistry(pReg);
}

void CSipServer::OnRequest(const ISIPRequest& Request)
{
    m_pImpl->OnRequest(Request);
}

void CSipServer::OnResponse(const ISIPResponse& Response)
{
    m_pImpl->OnResponse(Response);
}