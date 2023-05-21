#ifndef _CSDPATTRIBUTEIMPL_H_
#define _CSDPATTRIBUTEIMPL_H_

#include "ISdpAttribute.h"
#include "CKeyValuePairImpl.h"

//! @copydoc ISdpAttribute
class CSdpAttributeImpl : public ISdpAttribute
{
private:
    CKeyValuePairImpl m_data;

public:
    CSdpAttributeImpl();

    //! @name Overrides from #ISdpField
    //! @{
    ESdpType Type() const override;
    //! @}
    
    //! @name Overrides from #IKeyValuePair
    //! @{
    const char* Key() const override;

    void Key(const char*) override;

    const char* Value() const override;

    void Value(const char*) override;
    //! @}
    
    //! @name Overrides from #IField
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
};

#endif