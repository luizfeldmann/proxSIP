#ifndef _ISIPVIA_H_
#define _ISIPVIA_H_

#include "ISipField.h"

//! Indicates the transport used for the transaction and identifies the location where the response is to be sent
class PROXSIP_API ISipVia : public ISipField
{
public:
    //! Copies from another via
    virtual void Assign(const ISipVia&) = 0;

    //! Read the protocol version
    virtual const char* Version() const = 0;

    //! Sets the protocol version
    virtual void Version(const char*) = 0;

    //! Reads the transport
    virtual const char* Transport() const = 0;

    //! Sets the transport
    virtual void Transport(const char*) = 0;

    //! Reads the URI
    virtual const char* URI() const = 0;

    //! Sets the URI
    virtual void URI(const char*) = 0;
};

#endif