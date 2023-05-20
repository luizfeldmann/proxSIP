#ifndef _CSDPMEDIAIMPL_H_
#define _CSDPMEDIAIMPL_H_

#include "ISdpMedia.h"
#include "CSdpAttributeImpl.h"
#include "TContainer.h"

//! @copydoc ISdpMedia
class CSdpMediaImpl : public ISdpMedia
{
private:
    //! Collection of media-level attributes
    TContainer<ISdpAttribute, CSdpAttributeImpl> m_attribs;

public:
    CSdpMediaImpl();

    //! @name Overrides from #ISdpMedia
    //! @{
    const IContainer<ISdpAttribute>& Attributes() const override;

    IContainer<ISdpAttribute>& Attributes() override;
    //! @}

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