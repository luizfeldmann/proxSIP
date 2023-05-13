#ifndef _ISIPCONTACT_H_
#define _ISIPCONTACT_H_

#include "ISipField.h"

//! Parses or serializes the "Contact", "To", "From" fields of a SIP message
class PROXSIP_API ISipContact : public ISipField
{
public:
    
    //! Reads the display name
    virtual const char* Name() const = 0;

    //! Sets the display name
    virtual void Name(const char*) = 0;

    //! Reads the URI
    virtual const char* URI() const = 0;

    //! Sets the URI
    virtual void URI(const char*) = 0;
};

#endif