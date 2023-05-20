#ifndef _CSDPCONNECTIONIMPL_H_
#define _CSDPCONNECTIONIMPL_H_

#include "ISdpConnection.h"

//! @copydoc ISdpConnection
class CSdpConnectionImpl : public ISdpConnection
{
public:
    CSdpConnectionImpl();

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