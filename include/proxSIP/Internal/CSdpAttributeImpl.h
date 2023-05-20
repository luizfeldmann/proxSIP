#ifndef _CSDPATTRIBUTEIMPL_H_
#define _CSDPATTRIBUTEIMPL_H_

#include "ISdpAttribute.h"

//! @copydoc ISdpAttribute
class CSdpAttributeImpl : public ISdpAttribute
{
public:
    CSdpAttributeImpl();

    //! @name Overrides from #ISdpField
    //! @{
    ESdpType Type() const override;
    //! @}
    
    //! @name Overrides from #IField
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
};

#endif