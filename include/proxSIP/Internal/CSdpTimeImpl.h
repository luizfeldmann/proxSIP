#ifndef _CSDPTIMEIMPL_H_
#define _CSDPTIMEIMPL_H_

#include "ISdpTime.h"

//! @copybrief ISdpTime
class CSdpTimeImpl : public ISdpTime
{
private:
    //! Time the session starts
    unsigned long long m_uStartTime;

    // Time the session ends
    unsigned long long m_uEndTime;

public:
    CSdpTimeImpl();

    //! @name Overrides from #ISdpField
    //! @{
    ESdpType Type() const override;
    //! @}
    
    //! @name Overrides from #ISdpTime
    //! @{
    unsigned long long StartTime() const override;

    void StartTime(unsigned long long) override;

    unsigned long long EndTime() const override;

    void EndTime(unsigned long long) override;
    //! @} 

    //! @name Overrides from #IField
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
};

#endif