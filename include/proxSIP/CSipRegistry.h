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
    void Register(const char* sUser, const char* sLocation, unsigned int uExpires) override;

    const char* Locate(const char* sUser) const override;
    //! @}
};

#endif