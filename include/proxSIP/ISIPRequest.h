#ifndef _ISIPREQUEST_H_
#define _ISIPREQUEST_H_

#include "ISIPMessage.h"
#include "ESipMethods.h"

//! Representation of the data of a SIP request
class PROXSIP_API ISIPRequest : public ISIPMessage
{
public:
    virtual ~ISIPRequest() = default;

    //! Reads the method
    virtual ESipMethod Method() const = 0;

    //! Sets the method
    virtual void Method(ESipMethod) = 0;

    //! Reads the request URI
    virtual const char* URI() const = 0;

    //! Sets the request URI
    virtual void URI(const char*) = 0;
};

#endif