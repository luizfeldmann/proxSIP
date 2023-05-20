#ifndef _CSDPORIGINATORIMPL_H_
#define _CSDPORIGINATORIMPL_H_

#include "ISdpOriginator.h"
#include <string>

//! @copydoc ISdpOriginator
class CSdpOriginatorImpl : public ISdpOriginator
{
private:
    //! Login on the originating host
    std::string m_sUser;

    //! Globally unique identifier for the session
    unsigned int m_uSessId;

    //! Version number for this session description
    unsigned int m_uSessVersion;

    //! The type of network
    ESdpNetType m_eNetType;

    //! The type of the address that follows
    ESdpAddrType m_eAddrType;

    //! The address of the machine from which the session was created
    std::string m_sAddress;

public:
    CSdpOriginatorImpl();

    //! @name Overrides from #ISdpField
    //! @{
    ESdpType Type() const override;
    //! @}
    
    //! @name Overrides from #ISdpOriginator
    //! @{
    const char* User() const override;

    void User(const char*) override;

    unsigned int SessionID() const override;

    void SessionID(unsigned int) override;

    unsigned int SessionVersion() const override;

    void SessionVersion(unsigned int) override;

    ESdpNetType NetworkType() const override;

    void NetworkType(ESdpNetType) override;

    ESdpAddrType AddressType() const override;

    void AddressType(ESdpAddrType) override;

    const char* Address() const override;

    void Address(const char*) override;
    //! @}
    

    //! @name Overrides from #IField
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
};

#endif