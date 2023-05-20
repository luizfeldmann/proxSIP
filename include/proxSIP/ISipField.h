#ifndef _ISIPFIELD_H_
#define _ISIPFIELD_H_

#include "IField.h"
#include "IKeyValueCollection.h"

//! A structured representation of a known SIP field format
class PROXSIP_API ISipField : public IField
{
public:
    virtual ~ISipField() = default;

    // Copies from another object
    virtual void Assign(const ISipField&) = 0;

    //! Accessor to the aditional parameters
    virtual const IKeyValueCollection& Parameters() const = 0;

    //! Mutator to the aditional parameters
    virtual IKeyValueCollection& Parameters() = 0;
};

#endif