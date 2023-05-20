#include "Internal/CSdpAttributeImpl.h"

CSdpAttributeImpl::CSdpAttributeImpl()
{

}

/* Overrides from #ISdpField */
ESdpType CSdpAttributeImpl::Type() const
{
    return ESdpType::Attribute;
}

/* Overrides from #IField */
bool CSdpAttributeImpl::Parse(const char*, size_t)
{
    // TODO
    return true;
}

void CSdpAttributeImpl::Serialize(IOutputBuffer&) const
{
    // TODO
}