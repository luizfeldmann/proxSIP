#ifndef _CRTPMESSAGE_H_
#define _CRTPMESSAGE_H_

#include "IRtpMessage.h"

class CRtpMessageImpl;

//! @copydoc IRtpMessage
class PROXSIP_API CRtpMessage : public IRtpMessage
{
private:
    CRtpMessageImpl* m_pImpl;

    CRtpMessage(const CRtpMessage&) = delete;
    CRtpMessage& operator=(const CRtpMessage&) = delete;

public:
    CRtpMessage();
    ~CRtpMessage();

    //! @name Overrides from #IRtpMessage
    //! @{
    unsigned char Version() const override;

    void Version(unsigned char) override;

    bool Padding() const override;

    void Padding(bool) override;

    bool Extension() const override;

    void Extension(bool) override;

    bool Marker() const override;

    void Marker(bool) override;

    unsigned char PayloadType() const override;

    void PayloadType(unsigned char) override;

    unsigned short SequenceNumber() const override;

    void SequenceNumber(unsigned short) override;

    unsigned int Timestamp() const override;

    void Timestamp(unsigned int) override;

    unsigned int SSRC() const override;

    void SSRC(unsigned int) override;

    const IContainer<unsigned int>& CSRC() const override;

    IContainer<unsigned int>& CSRC() override;

    const IBuffer& Payload() const override;

    IBuffer& Payload() override;
    //! @}

    //! @name Overrides from IRtpMessage
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
};

#endif