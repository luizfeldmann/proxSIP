#ifndef _IENDPOINT_H_
#define _IENDPOINT_H_

#include "proxSIPExports.h"

class PROXSIP_API IEndpoint
{
public:
    virtual ~IEndpoint() = default;

    //! Sets the address
    virtual void Address(const char*) = 0;

    //! Reads the address
    virtual const char* Address() const = 0;

    //! Sets both the address and the port
    virtual void Assign(const char*, unsigned short) = 0;

    //! Sets both the address and the port
    virtual void Assign(const IEndpoint&) = 0;

    //! Sets the port
    virtual void Port(unsigned short) = 0;

    //! Reads the port
    virtual unsigned short Port() const = 0;
};

#endif