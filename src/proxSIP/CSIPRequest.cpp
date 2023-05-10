#include "CSIPRequest.h"
#include "Internal/CSIPRequestImpl.h"

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
    return m_pImpl->Type();
}

const char* CSIPRequest::Version() const
{
    return m_pImpl->Version();
}

void CSIPRequest::Version(const char* szVersion)
{
    m_pImpl->Version(szVersion);
}

const IEndpoint& CSIPRequest::Source() const
{
    return m_pImpl->Source();
}

IEndpoint& CSIPRequest::Source()
{
    return m_pImpl->Source();
}

const IEndpoint& CSIPRequest::Destination() const
{
    return m_pImpl->Destination();
}

IEndpoint& CSIPRequest::Destination()
{
    return m_pImpl->Destination();
}

const IKeyValueCollection& CSIPRequest::Fields() const
{
    return m_pImpl->Fields();
}

IKeyValueCollection& CSIPRequest::Fields()
{
    return m_pImpl->Fields();
}

const IBuffer& CSIPRequest::Content() const
{
    return m_pImpl->Content();
}

IBuffer& CSIPRequest::Content()
{
    return m_pImpl->Content();
}

/* Overrides from ISIPRequest */

ESipMethod CSIPRequest::Method() const
{
    return m_pImpl->Method();
}

void CSIPRequest::Method(ESipMethod eMethod)
{
    m_pImpl->Method(eMethod);
}

const char* CSIPRequest::URI() const
{
    return m_pImpl->URI();
}

void CSIPRequest::URI(const char* szURI)
{
    m_pImpl->URI(szURI);
}