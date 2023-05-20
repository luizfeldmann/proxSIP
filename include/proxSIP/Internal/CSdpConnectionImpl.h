#ifndef _CSDPCONNECTIONIMPL_H_
#define _CSDPCONNECTIONIMPL_H_

#include "ISdpConnection.h"
#include <string>

//! @copydoc ISdpConnection
class CSdpConnectionImpl : public ISdpConnection
{
private:
    //! The type of network
    ESdpNetType m_eNetType;

    //! The type of the address that follows
    ESdpAddrType m_eAddrType;

    //! The address of the machine from which the session was created
    std::string m_sAddress;

    //! Time to live
    unsigned int m_uTTL;

    //! Number of addresses
    unsigned int m_uNumAddr;

public:
    CSdpConnectionImpl();

    //! @name Overrides from #ISdpField
    //! @{
    ESdpType Type() const override;
    //! @}
     
    
    //! @name Overrides from #ISdpConnection
    //! @{
    ESdpNetType NetworkType() const override;

    void NetworkType(ESdpNetType) override;

    ESdpAddrType AddressType() const override;

    void AddressType(ESdpAddrType) override;

    const char* Address() const override;

    void Address(const char*) override;

    unsigned int TTL() const override;

    void TTL(unsigned int) override;

    unsigned int Count() const override;

    void Count(unsigned int) override;
    //! @} 

    //! @name Overrides from #IField
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
};

#endif