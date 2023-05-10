#include "Internal/CSIPResponseImpl.h"

CSIPResponseImpl::CSIPResponseImpl()
{

}

CSIPResponseImpl::CSIPResponseImpl(const CSIPResponseImpl&) = default;

CSIPResponseImpl& CSIPResponseImpl::operator=(const CSIPResponseImpl&) = default;

CSIPResponseImpl::CSIPResponseImpl(CSIPResponseImpl&&) noexcept = default;

CSIPResponseImpl& CSIPResponseImpl::operator=(CSIPResponseImpl&&) noexcept = default;

const ESIPMessageType CSIPResponseImpl::Type() const
{
    return ESIPMessageType::Response;
}