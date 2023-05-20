#ifndef _ISDPORIGINATOR_H_
#define _ISDPORIGINATOR_H_

#include "ISdpField.h"

//! The originator of the session (username and the address of the user’s host)
//! plus a session identifier and version number
class PROXSIP_API ISdpOriginator : public ISdpField
{
public:
    virtual ~ISdpOriginator() = default;

    //! Reads the user name
    virtual const char* User() const = 0;

    //! Sets the user name
    virtual void User(const char*) = 0;

    //! Reads the ID of the session
    virtual unsigned int SessionID() const = 0;

    //! Sets the ID of the session
    virtual void SessionID(unsigned int) = 0;

    //! Reads the version of the session description
    virtual unsigned int SessionVersion() const = 0;

    //! Sets the version of the session description
    virtual void SessionVersion(unsigned int) = 0;

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
};

#endif