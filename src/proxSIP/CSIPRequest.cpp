#include "CSIPRequest.h"
#include "CEndpoint.h"

/* CSIPRequestImpl */

class CSIPRequestImpl
{
public:
    CEndpoint m_edpSrc;
    CEndpoint m_edpDst;

    CSIPRequestImpl()
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