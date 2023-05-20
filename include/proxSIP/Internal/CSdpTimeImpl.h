#ifndef _CSDPTIMEIMPL_H_
#define _CSDPTIMEIMPL_H_

#include "ISdpTime.h"

//! @copybrief ISdpTime
class CSdpTimeImpl : public ISdpTime
{
public:
    CSdpTimeImpl();

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