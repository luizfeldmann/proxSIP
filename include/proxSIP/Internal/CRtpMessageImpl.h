#ifndef _CRTPMESSAGEIMPL_H_
#define _CRTPMESSAGEIMPL_H_

#include "IRtpMessage.h"
#include "TContainer.h"
#include "TBuffer.h"

//! @copydoc #IRtpMessage
class CRtpMessageImpl : public IRtpMessage
{
private:
    struct SRtpData
    {
        union {
            unsigned char a;
            struct {
                unsigned char m_uCsrc : 4;
                bool m_bExtension : 1;
                bool m_bPadding : 1;
                unsigned char m_uVersion : 2;
            };
        };
        union {
            unsigned char b;
            struct {
                unsigned char m_uPayloadType : 7;
                bool m_bMarker : 1;
            };
        };
        unsigned short m_uSequence;
        unsigned int m_uTimestamp;
        unsigned int m_SynchSource;
    } m_stData;

    static_assert(sizeof(m_stData) == 12, "RTP packing wrong");

    //! List of contributing sources
    TContainer<unsigned int, unsigned int> m_vCSRC;

    //! Payload data
    TBuffer<std::vector<char>> m_bufPayload;

public:
    CRtpMessageImpl();

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