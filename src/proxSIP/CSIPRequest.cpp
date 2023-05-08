#include "CSIPRequest.h"
#include "CEndpoint.h"
#include <string>

/* CSIPRequestImpl */

class CSIPRequestImpl
{
public:
    CEndpoint m_edpSrc;
    CEndpoint m_edpDst;

    ESipMethod m_eMethod;
    std::string m_sURI;
    std::string m_sVersion;

    CSIPRequestImpl()
        : m_eMethod(ESipMethod::Unknown)
    {

    }
};

/* CSIPRequest */

CSIPRequest::~CSIPRequest()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

CSIPRequest::CSIPRequest()
    : m_pImpl(new CSIPRequestImpl)
{

}

/* Overrides from ISIPMessage */

const ESIPMessageType CSIPRequest::Type() const
{
    return ESIPMessageType::Request;
}

const IEndpoint& CSIPRequest::Source() const
{
    return m_pImpl->m_edpSrc;
}

IEndpoint& CSIPRequest::Source()
{
    return m_pImpl->m_edpSrc;
}

const IEndpoint& CSIPRequest::Destination() const
{
    return m_pImpl->m_edpDst;
}

IEndpoint& CSIPRequest::Destination()
{
    return m_pImpl->m_edpDst;
}

/* Overrides from ISIPRequest */

ESipMethod CSIPRequest::Method() const
{
    return m_pImpl->m_eMethod;
}

void CSIPRequest::Method(ESipMethod eMethod)
{
    m_pImpl->m_eMethod = eMethod;
}

const char* CSIPRequest::URI() const
{
    return m_pImpl->m_sURI.c_str();
}

void CSIPRequest::URI(const char* szURI)
{
    m_pImpl->m_sURI = szURI;
}

const char* CSIPRequest::Version() const
{
    return m_pImpl->m_sVersion.c_str();
}

void CSIPRequest::Version(const char* szVersion)
{
    m_pImpl->m_sVersion = szVersion;
}