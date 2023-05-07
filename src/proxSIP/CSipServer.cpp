#include "CSipServer.h"

/* CSipServerImpl */
class CSipServerImpl
{
public:
    CSipServerImpl()
    {

    }
};

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

void CSipServer::OnRequest(const ISIPRequest&)
{

}

void CSipServer::OnResponse(const ISIPResponse&)
{

}