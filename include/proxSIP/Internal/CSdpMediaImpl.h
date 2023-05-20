#ifndef _CSDPMEDIAIMPL_H_
#define _CSDPMEDIAIMPL_H_

#include "ISdpMedia.h"

//! @copydoc ISdpMedia
class CSdpMediaImpl : public ISdpMedia
{
public:
    CSdpMediaImpl();

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