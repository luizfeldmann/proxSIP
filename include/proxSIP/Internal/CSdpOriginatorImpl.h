#ifndef _CSDPORIGINATORIMPL_H_
#define _CSDPORIGINATORIMPL_H_

#include "ISdpOriginator.h"

//! @copydoc ISdpOriginator
class CSdpOriginatorImpl : public ISdpOriginator
{
public:
    CSdpOriginatorImpl();

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