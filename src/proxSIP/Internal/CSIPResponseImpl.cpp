#include "Internal/CSIPResponseImpl.h"

/* CSIPResponseImpl */

CSIPResponseImpl::CSIPResponseImpl()
{

}

CSIPResponseImpl::CSIPResponseImpl(const CSIPResponseImpl&) = default;

CSIPResponseImpl& CSIPResponseImpl::operator=(const CSIPResponseImpl&) = default;

CSIPResponseImpl::CSIPResponseImpl(CSIPResponseImpl&&) noexcept = default;

CSIPResponseImpl& CSIPResponseImpl::operator=(CSIPResponseImpl&&) noexcept = default;

/* ISIPMessage */

const ESIPMessageType CSIPResponseImpl::Type() const
{
    return ESIPMessageType::Response;
}

/* ISIPRequest */

ESipStatusCode CSIPResponseImpl::Status() const
{
    return m_eStatus;
}

void CSIPResponseImpl::Status(ESipStatusCode eStatus)
{
    m_eStatus = eStatus;
}