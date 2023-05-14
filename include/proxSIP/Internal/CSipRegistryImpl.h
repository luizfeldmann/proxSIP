#ifndef _CSIPREGISTRYIMPL_H_
#define _CSIPREGISTRYIMPL_H_

#include "ISipRegistry.h"
#include <map>
#include <string>
#include <chrono>

//! Internal data stored by the #CSipRegistryImpl
struct SRegistryData
{
    //! Record where the contact can be found
    std::string m_sLocation;

    //! Absolute time when this registration expires
    std::chrono::system_clock::time_point m_expires;
};

//! @copydoc ISipRegistry
class CSipRegistryImpl : public ISipRegistry
{
private:
    using map_t = std::map<std::string, SRegistryData>;
    map_t m_mReg;

public:
    CSipRegistryImpl();

    //! @name Overrides from #ISipRegistry
    //! @{
    void Register(const char* sUser, const char* sLocation, unsigned int uExpires) override;

    const char* Locate(const char* sUser) const override;
    //! @}
};

#endif