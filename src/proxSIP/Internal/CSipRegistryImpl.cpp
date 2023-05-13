#include "Internal/CSipRegistryImpl.h"

CSipRegistryImpl::CSipRegistryImpl()
{

}

/* Overrides from ISipRegistry */

void CSipRegistryImpl::Register(const char*, const ISipContact& Contact, const ISipVia& Via)
{

}

bool CSipRegistryImpl::Locate(const char*, const ISipContact& Contact, ISipVia& Via) const
{
    return false;
}