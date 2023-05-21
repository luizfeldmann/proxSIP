#ifndef _ISDPRTPMAP_H_
#define _ISDPRTPMAP_H_

#include "ISdpField.h"

//! Maps from an RTP payload type number to an encoding name denoting the payload format
//! and also provides information on the clock rate and encoding parameters
class PROXSIP_API ISdpRtpMap : public ISdpField
{
public:
    virtual ~ISdpRtpMap() = default;
    
    //! Reads the payload type
    virtual unsigned char PayloadType() const = 0;

    //! Sets the payload type
    virtual void PayloadType(unsigned char) = 0;

    //! Reads the encoding name
    virtual const char* EncodingName() const = 0;

    //! Sets the encoding name
    virtual void EncodingName(const char*) = 0;

    //! Reads the clock rate
    virtual unsigned short ClockRate() const = 0;

    //! Sets the clock rate
    virtual void ClockRate(unsigned short) = 0;

    //! Reads the parameters
    virtual const char* Parameters() const = 0;

    //! Sets the parameters
    virtual void Parameters(const char*) = 0;
};

#endif