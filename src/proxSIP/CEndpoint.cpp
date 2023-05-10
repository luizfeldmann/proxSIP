#include "CEndpoint.h"
#include <string>

/* CEndpointImpl */

class CEndpointImpl
{
public:
    std::string m_sAddr;
    unsigned short m_usPort;

    CEndpointImpl(const CEndpointImpl&) = default;

    CEndpointImpl& operator=(const CEndpointImpl&) = default;

    CEndpointImpl(const char* szAddr = "", unsigned short usPort = 0)
        : m_sAddr(szAddr)
        , m_usPort(usPort)
    {

    }

    CEndpointImpl(const IEndpoint& other)
        : CEndpointImpl(other.Address(), other.Port())
    {

    }
};

IMPLEMENT_PIMPL(CEndpointImpl);

/* CEndpoint */

CEndpoint::CEndpoint()
    : TImplPtr(new CEndpointImpl)
{

}

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
    m_pImpl->m_sAddr = szAddr;
}

const char* CEndpoint::Address() const
{
    return m_pImpl->m_sAddr.c_str();
}

void CEndpoint::Port(unsigned short usPort)
{
    m_pImpl->m_usPort = usPort;
}

unsigned short CEndpoint::Port() const
{
    return m_pImpl->m_usPort;
}

void CEndpoint::Assign(const char* szAddr, unsigned short usPort)
{
    m_pImpl->m_sAddr = szAddr;
    m_pImpl->m_usPort = usPort;
}