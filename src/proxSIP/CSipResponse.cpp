#include "CSIPResponse.h"
#include "CEndpoint.h"

/* CSIPResponseImpl */

class CSIPResponseImpl
{
public:
    CEndpoint m_edpSrc;
    CEndpoint m_edpDst;

    CSIPResponseImpl()
    {

    }
};

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
    return ESIPMessageType::Response;
}

const IEndpoint& CSIPResponse::Source() const
{
    return m_pImpl->m_edpSrc;
}

IEndpoint& CSIPResponse::Source()
{
    return m_pImpl->m_edpSrc;
}

const IEndpoint& CSIPResponse::Destination() const
{
    return m_pImpl->m_edpDst;
}

IEndpoint& CSIPResponse::Destination()
{
    return m_pImpl->m_edpDst;
}