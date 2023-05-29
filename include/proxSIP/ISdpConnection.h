#ifndef _ISDPCONNECTION_H_
#define _ISDPCONNECTION_H_

#include "ISdpField.h"

//! Connection information from the session user agent
class PROXSIP_API ISdpConnection : public ISdpField
{
public:
    virtual ~ISdpConnection() = default;

    //! Reads the network type
    virtual ESdpNetType NetworkType() const = 0;

    //! Sets the type of the network
    virtual void NetworkType(ESdpNetType) = 0;

    //! Reads the address type
    virtual ESdpAddrType AddressType() const = 0;

    //! Sets the type of the address
    virtual void AddressType(ESdpAddrType) = 0;

    //! Reads the originator address
    virtual const char* Address() const = 0;

    //! Sets the originator address
    virtual void Address(const char*) = 0;

    //! Reads the time-to-live
    virtual unsigned int TTL() const = 0;

    //! Sets the time-to-live
    virtual void TTL(unsigned int) = 0;

    //! Reads the number of addresses
    virtual unsigned int Count() const = 0;

    //! Sets the number of addresses
    virtual void Count(unsigned int) = 0;
};

#endif