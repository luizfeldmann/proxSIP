#ifndef _ISIPFIELD_H_
#define _ISIPFIELD_H_

#include "IBuffer.h"

//! A structured representation of a known SIP field format
class PROXSIP_API ISipField
{
public:
    virtual ~ISipField() = default;

    //! Parses the field
    virtual bool Parse(const char*, size_t) = 0;

    //! Serializes the field to a string
    virtual void Serialize(IBuffer&) const = 0;
};

#endif