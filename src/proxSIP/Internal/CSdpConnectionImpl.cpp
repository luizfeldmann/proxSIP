#include "Internal/CSdpConnectionImpl.h"

CSdpConnectionImpl::CSdpConnectionImpl()
{

}

/* Overrides from #ISdpField */
ESdpType CSdpConnectionImpl::Type() const
{
    return ESdpType::Connection;
}

/* Overrides from #IField */
bool CSdpConnectionImpl::Parse(const char*, size_t)
{
    // TODO
    return true;
}

void CSdpConnectionImpl::Serialize(IOutputBuffer&) const
{
    // TODO
}