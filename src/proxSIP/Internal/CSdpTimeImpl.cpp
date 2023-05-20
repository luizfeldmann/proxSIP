#include "Internal/CSdpTimeImpl.h"

CSdpTimeImpl::CSdpTimeImpl()
{

}

/* Overrides from #ISdpField */
ESdpType CSdpTimeImpl::Type() const
{
    return ESdpType::Time;
}

/* Overrides from #IField */
bool CSdpTimeImpl::Parse(const char*, size_t)
{
    // TODO
    return true;
}

void CSdpTimeImpl::Serialize(IOutputBuffer&) const
{
    // TODO
}