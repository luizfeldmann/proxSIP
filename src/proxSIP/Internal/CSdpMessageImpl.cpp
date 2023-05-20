#include "Internal/CSdpMessageImpl.h"
#include "ESdpType.h"

CSdpMessageImpl::CSdpMessageImpl()
    : m_uVersion(0)
{

}

/* Overrides from ISdpMessage */

/* Overrides from IMessage */

bool CSdpMessageImpl::Parse(const char*, size_t)
{


    return false;
}

void CSdpMessageImpl::Serialize(IOutputBuffer&) const
{

}