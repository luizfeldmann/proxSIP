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

void CSipRegistry::Register(const char* sDomain, const ISipContact& Contact, const ISipVia& Via)
{
    m_pImpl->Register(sDomain, Contact, Via);
}

bool CSipRegistry::Locate(const char* sDomain, const ISipContact& Contact, ISipVia& Via) const
{
    return m_pImpl->Locate(sDomain, Contact, Via);
}