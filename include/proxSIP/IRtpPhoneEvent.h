#ifndef _IRTPPHONEEVENT_H_
#define _IRTPPHONEEVENT_H_

#include "IRtpPayload.h"

//! Event codes for DTMF over RTP
enum class EPhoneEventCode
{
    Num0     = 0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    Asterisk = 10,
    Pound    = 11,
    KeyA     = 12,
    KeyB     = 13,
    KeyC     = 14,
    KeyD     = 15,
};

//! Represents DTMF events carried over RTP
class PROXSIP_API IRtpPhoneEvent : public IRtpPayload
{
public:
    virtual ~IRtpPhoneEvent() = default;

    //! Reads the event code
    virtual EPhoneEventCode EventCode() const = 0;

    //! Sets the event code
    virtual void EventCode(EPhoneEventCode) = 0;

    //! Reads the 'end' flag
    virtual bool End() const = 0;

    //! Sets the 'end' flag
    virtual void End(bool) = 0;

    //! Reads the volume of the event [abs dBm0]
    virtual unsigned char Volume() const = 0;

    //! Sets the volume of the tone [abs dBm0]
    virtual void Volume(unsigned char) = 0;

    //! Reads the duration of the event [timestamp units]
    virtual unsigned short Duration() const = 0;

    //! Sets the duration of the event [timestamp units]
    virtual void Duration(unsigned short) = 0;
};

#endif
