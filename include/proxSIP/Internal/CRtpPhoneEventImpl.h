#ifndef _CRTPPHONEEVENTIMPL_H_
#define _CRTPPHONEEVENTIMPL_H_

#include "IRtpPhoneEvent.h"

//! @copybrief IRtpPhoneEvent
class CRtpPhoneEventImpl : public IRtpPhoneEvent
{
private:
    struct SPhoneEventData {
        unsigned char m_uEvtCode;
        struct
        {
            unsigned char m_uVolume : 6;
            unsigned char m_uReserv : 1;
            unsigned char m_uEnd : 1;
        };
        unsigned short m_uDuration;

        SPhoneEventData();
    } m_stData;

    static_assert(sizeof(m_stData) == 4, "Wrong layout of phone event data struct");

public:
    CRtpPhoneEventImpl();

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
