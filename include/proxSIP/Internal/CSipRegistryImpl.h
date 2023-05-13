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
    std::string m_sViaURI;

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
    void Register(const char* sDomain, const ISipContact& Contact, const ISipVia& Via) override;

    bool Locate(const char* sDomain, const ISipContact& Contact, ISipVia& Via) const override;
    //! @}
};

#endif