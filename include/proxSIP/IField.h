#ifndef _IFIELD_H_
#define _IFIELD_H_

#include "IOutputBuffer.h"

//! A structured representation of a known field in a message
class PROXSIP_API IField
{
public:
    virtual ~IField() = default;

    //! Parses the field
    virtual bool Parse(const char*, size_t) = 0;

    //! Serializes the field to a string
    virtual void Serialize(IOutputBuffer&) const = 0;
};

#endif