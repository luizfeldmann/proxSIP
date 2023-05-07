#include "CEndpoint.h"
#include <string>

/* CEndpointImpl */

class CEndpointImpl
{
public:
    std::string m_sAddr;
    unsigned short m_usPort;

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

/* CEndpoint */

CEndpoint::~CEndpoint()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

CEndpoint::CEndpoint()
    : m_pImpl(new CEndpointImpl)
{

}

CEndpoint::CEndpoint(const char* szAddr, unsigned short uPort)
    : m_pImpl(new CEndpointImpl(szAddr, uPort))
{

}

CEndpoint::CEndpoint(const IEndpoint& other)
    : m_pImpl(new CEndpointImpl(other))
{

}

CEndpoint::CEndpoint(const CEndpoint& other)
    : m_pImpl(new CEndpointImpl(other))
{

}

CEndpoint& CEndpoint::operator=(const IEndpoint& other)
{
    *m_pImpl = CEndpointImpl(other);
    return *this;
}

CEndpoint& CEndpoint::operator=(const CEndpoint& other)
{
    *m_pImpl = CEndpointImpl(other);
    return *this;
}

CEndpoint::CEndpoint(CEndpoint&& other) noexcept
    : m_pImpl(other.m_pImpl)
{
    other.m_pImpl = nullptr;
}

CEndpoint& CEndpoint::operator=(CEndpoint&& other) noexcept
{
    std::swap(m_pImpl, other.m_pImpl);
    return *this;
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