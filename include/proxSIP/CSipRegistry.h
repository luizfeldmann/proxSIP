#ifndef _CSIPREGISTRY_H_
#define _CSIPREGISTRY_H_

#include "ISipRegistry.h"

class CSipRegistryImpl;

//! @copydoc ISipRegistry
class PROXSIP_API CSipRegistry : public ISipRegistry
{
private:
    CSipRegistryImpl* m_pImpl;

    CSipRegistry(const CSipRegistry&) = delete;
    CSipRegistry& operator=(const CSipRegistry&) = delete;

public:
    CSipRegistry();
    ~CSipRegistry();

    //! @name Overrides from #ISipRegistry
    //! @{
    void Register(const char* sDomain, const ISipContact& Contact, const ISipVia& Via) override;

    bool Locate(const char* sDomain, const ISipContact& Contact, ISipVia& Via) const override;
    //! @}
};

#endif