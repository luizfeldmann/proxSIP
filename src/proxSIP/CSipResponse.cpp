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

/* Overrides from ISIPMessage */

const ESIPMessageType CSIPResponse::Type() const
{
    return m_pImpl->Type();
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

const IBuffer& CSIPResponse::Content() const
{
    return m_pImpl->Content();
}

IBuffer& CSIPResponse::Content()
{
    return m_pImpl->Content();
}