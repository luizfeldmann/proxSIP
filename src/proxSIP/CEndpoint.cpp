#include "CEndpoint.h"
#include "Internal/CEndpointImpl.h"

/* CEndpointImpl */

IMPLEMENT_PIMPL(CEndpointImpl);

/* CEndpoint */

CEndpoint::CEndpoint(const char* szAddr, unsigned short uPort)
    : TImplPtr(new CEndpointImpl(szAddr, uPort))
{

}

CEndpoint::CEndpoint(const IEndpoint& other)
    : TImplPtr(new CEndpointImpl(other))
{

}

void CEndpoint::Assign(const IEndpoint& other)
{
    *m_pImpl = CEndpointImpl(other);
}

void CEndpoint::Address(const char* szAddr)
{
    m_pImpl->Address(szAddr);
}

const char* CEndpoint::Address() const
{
    return m_pImpl->Address();
}

void CEndpoint::Port(unsigned short usPort)
{
    m_pImpl->Port(usPort);
}

unsigned short CEndpoint::Port() const
{
    return m_pImpl->Port();
}

void CEndpoint::Assign(const char* szAddr, unsigned short usPort)
{
    m_pImpl->Assign(szAddr, usPort);
}