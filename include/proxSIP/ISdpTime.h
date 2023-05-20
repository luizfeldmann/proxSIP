#ifndef _ISDPTIME_H_
#define _ISDPTIME_H_

#include "ISdpField.h"

//! Specify the start and stop times for a session
class PROXSIP_API ISdpTime : public ISdpField
{
public:
    virtual ~ISdpTime() = default;

    //! Reads the start time
    virtual unsigned long long StartTime() const = 0;

    //! Sets the start time
    virtual void StartTime(unsigned long long) = 0;

    //! Reads the ending time
    virtual unsigned long long EndTime() const = 0;

    //! Sets the ending time
    virtual void EndTime(unsigned long long) = 0;
};

#endif