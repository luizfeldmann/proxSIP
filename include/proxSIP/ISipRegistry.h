#ifndef _ISIPREGISTRY_H_
#define _ISIPREGISTRY_H_

#include "proxSIPExports.h"

//! Registers contacts' locations
class PROXSIP_API ISipRegistry
{
public:
    virtual ~ISipRegistry() = default;

    //! Store a contact information and associated location
    virtual void Register(const char* sUser, const char* sLocation, unsigned int uExpires) = 0;

    // Retrieves the location associated to the contact
    virtual const char* Locate(const char* sUser) const = 0;
};

#endif