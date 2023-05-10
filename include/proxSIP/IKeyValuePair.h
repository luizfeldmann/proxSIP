#ifndef _IKEYVALUEPAIR_H_
#define _IKEYVALUEPAIR_H_

#include "proxSIPExports.h"

//! Represents a "Key: Value" pair field
class PROXSIP_API IKeyValuePair
{
public:
    virtual ~IKeyValuePair() = default;

    //! Reads the key
    virtual const char* Key() const = 0;

    //! Reads the value
    virtual const char* Value() const = 0;

    //! Sets the value
    virtual void Value(const char*) = 0;
};

#endif