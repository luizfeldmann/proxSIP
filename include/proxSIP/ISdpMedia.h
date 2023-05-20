#ifndef _ISDPMEDIA_H_
#define _ISDPMEDIA_H_

#include "ISdpField.h"
#include "IContainer.h"
#include "ISdpAttribute.h"

//! Attributes convey additional information
class PROXSIP_API ISdpMedia : public ISdpField
{
public:
    virtual ~ISdpMedia() = default;

    //! Accessor to the collection of attributes
    virtual const IContainer<ISdpAttribute>& Attributes() const = 0;

    //! Mutator to the collection of attributes
    virtual IContainer<ISdpAttribute>& Attributes() = 0;
};

#endif