#ifndef _CRTPPHONEEVENT_H_
#define _CRTPPHONEEVENT_H_

#include "IRtpPhoneEvent.h"

class CRtpPhoneEventImpl;

//! @copybrief IRtpPhoneEvent
class PROXSIP_API CRtpPhoneEvent : public IRtpPhoneEvent
{
private:
    CRtpPhoneEventImpl* m_pImpl;

    CRtpPhoneEvent(const CRtpPhoneEvent&) = delete;
    CRtpPhoneEvent& operator=(const CRtpPhoneEvent&) = delete;

public:
    CRtpPhoneEvent();
    ~CRtpPhoneEvent();

    //! @name Overrides from #IRtpPhoneEvent
    //! @{
    EPhoneEventCode EventCode() const override;

    void EventCode(EPhoneEventCode) override;

    bool End() const override;

    void End(bool) override;

    unsigned char Volume() const override;

    void Volume(unsigned char) override;

    unsigned short Duration() const override;

    void Duration(unsigned short) override;
    //! @}
    
    //! @name Overrides from #IMessage
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
    
};

#endif