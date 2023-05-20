#include "Internal/CSdpMediaImpl.h"

CSdpMediaImpl::CSdpMediaImpl()
{

}

/* Overrides from #ISdpField */
ESdpType CSdpMediaImpl::Type() const
{
    return ESdpType::Media;
}

/* Overrides from #IField */
bool CSdpMediaImpl::Parse(const char*, size_t)
{
    // TODO
    return true;
}

void CSdpMediaImpl::Serialize(IOutputBuffer&) const
{
    // TODO
}