#include "Internal/CSdpOriginatorImpl.h"

CSdpOriginatorImpl::CSdpOriginatorImpl()
{

}

/* Overrides from #ISdpField */
ESdpType CSdpOriginatorImpl::Type() const
{
    return ESdpType::Originator;
}

/* Overrides from #IField */
bool CSdpOriginatorImpl::Parse(const char*, size_t)
{
    // TODO
    return true;
}

void CSdpOriginatorImpl::Serialize(IOutputBuffer&) const
{
    // TODO
}