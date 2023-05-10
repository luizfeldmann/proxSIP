#include "Internal/CEndpointImpl.h"

CEndpointImpl::CEndpointImpl(const CEndpointImpl&) = default;

CEndpointImpl& CEndpointImpl::operator=(const CEndpointImpl&) = default;

CEndpointImpl::CEndpointImpl(CEndpointImpl&&) noexcept = default;

CEndpointImpl& CEndpointImpl::operator=(CEndpointImpl&&) noexcept = default;

CEndpointImpl::CEndpointImpl(const char* szAddr, unsigned short usPort)
    : m_sAddr(szAddr)
    , m_usPort(usPort)
{

}

CEndpointImpl::CEndpointImpl(const IEndpoint& other)
    : CEndpointImpl(other.Address(), other.Port())
{

}

void CEndpointImpl::Address(const char* sAddr)
{
    m_sAddr = sAddr;
}

const char* CEndpointImpl::Address() const
{
    return m_sAddr.c_str();
}

void CEndpointImpl::Assign(const char* sAddr, unsigned short usPort)
{
    m_sAddr = sAddr;
    m_usPort = usPort;
}

void CEndpointImpl::Assign(const IEndpoint& copy)
{
    m_sAddr = copy.Address();
    m_usPort = copy.Port();
}

void CEndpointImpl::Port(unsigned short usPort)
{
    m_usPort = usPort;
}

unsigned short CEndpointImpl::Port() const
{
    return m_usPort;
}