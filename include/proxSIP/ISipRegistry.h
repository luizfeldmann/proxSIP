#ifndef _ISIPREGISTRY_H_
#define _ISIPREGISTRY_H_

#include "ISipContact.h"
#include "ISipVia.h"

//! Registers contacts' locations
class PROXSIP_API ISipRegistry
{
public:
    virtual ~ISipRegistry() = default;

    //! Store a contact information and associated location
    virtual void Register(const char* sDomain, const ISipContact& Contact, const ISipVia& Via) = 0;

    // Retrieves the location associated to the contact
    virtual bool Locate(const char* sDomain, const ISipContact& Contact, ISipVia& Via) const = 0;
};

#endif