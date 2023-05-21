#ifndef _ISDPATTRIBUTE_H_
#define _ISDPATTRIBUTE_H_

#include "ISdpField.h"
#include "IKeyValuePair.h"

//! Attributes convey additional information
class PROXSIP_API ISdpAttribute : public ISdpField, public IKeyValuePair
{
public:
    virtual ~ISdpAttribute() = default;
};

#endif