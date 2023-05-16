#ifndef _ISIPCONTACT_H_
#define _ISIPCONTACT_H_

#include "ISipField.h"
#include "ISipURI.h"

//! Parses or serializes the "Contact", "To", "From" fields of a SIP message
class PROXSIP_API ISipContact : public ISipField
{
public:
    
    //! Reads the display name
    virtual const char* Name() const = 0;

    //! Sets the display name
    virtual void Name(const char*) = 0;

    //! Reads the URI
    virtual const ISipURI& URI() const = 0;

    //! Sets the URI
    virtual ISipURI& URI() = 0;
};

#endif