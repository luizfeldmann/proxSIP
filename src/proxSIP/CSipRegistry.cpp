#include "CSIPRegistry.h"
#include "Internal/CSipRegistryImpl.h"

CSipRegistry::CSipRegistry()
    : m_pImpl(new CSipRegistryImpl)
{

}

CSipRegistry::~CSipRegistry()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

/* Overrides from #ISipRegistry */

void CSipRegistry::Register(const char* sUser, const char* sLocation, unsigned int uExpires)
{
    m_pImpl->Register(sUser, sLocation, uExpires);
}

const char* CSipRegistry::Locate(const char* sUser) const
{
    return m_pImpl->Locate(sUser);
}