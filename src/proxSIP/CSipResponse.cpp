#include "CSIPResponse.h"
#include "Internal/CSIPResponseImpl.h"

/* CSIPResponse */

CSIPResponse::~CSIPResponse()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

CSIPResponse::CSIPResponse()
    : m_pImpl(new CSIPResponseImpl)
{

}

/* Overrides from ISIPResponse */

ESipStatusCode CSIPResponse::Status() const
{
    return m_pImpl->Status();
}

void CSIPResponse::Status(ESipStatusCode eStatus)
{
    m_pImpl->Status(eStatus);
}

/* Overrides from ISIPMessage */

const ESIPMessageType CSIPResponse::Type() const
{
    return m_pImpl->Type();
}

const char* CSIPResponse::Version() const
{
    return m_pImpl->Version();
}

void CSIPResponse::Version(const char* sVersion)
{
    m_pImpl->Version(sVersion);
}

const IEndpoint& CSIPResponse::Source() const
{
    return m_pImpl->Source();
}

IEndpoint& CSIPResponse::Source()
{
    return m_pImpl->Source();
}

const IEndpoint& CSIPResponse::Destination() const
{
    return m_pImpl->Source();
}

IEndpoint& CSIPResponse::Destination()
{
    return m_pImpl->Source();
}

const IKeyValueCollection& CSIPResponse::Fields() const
{
    return m_pImpl->Fields();
}

IKeyValueCollection& CSIPResponse::Fields()
{
    return m_pImpl->Fields();
}

const IBuffer& CSIPResponse::Content() const
{
    return m_pImpl->Content();
}

IBuffer& CSIPResponse::Content()
{
    return m_pImpl->Content();
}