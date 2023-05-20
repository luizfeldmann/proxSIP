#ifndef _ISDPFIELD_H_
#define _ISDPFIELD_H_

#include "IField.h"
#include "ESdpType.h"

//! A structured representation of a known SDP field format
class PROXSIP_API ISdpField : public IField
{
public:
    virtual ~ISdpField() = default;

    //! Reflection of the field type
    virtual ESdpType Type() const = 0;
};

#endif