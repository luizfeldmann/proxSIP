#ifndef _CSDPRTPMAPIMPL_H_
#define _CSDPRTPMAPIMPL_H_

#include "ISdpRtpMap.h"
#include <string>

//! @copydoc #ISdpRtpMap
class CSdpRtpMapImpl : public ISdpRtpMap
{
private:
    // Type listed in the media field
    unsigned char m_uPayloadType;

    //! Name of payload encoding
    std::string m_sEncodingName;

    //! Frequency in Hz
    unsigned short m_uClockRate;

    //! Additional parameters
    std::string m_sParameters;

public:
    CSdpRtpMapImpl();

    //! @name Overrides from #ISdpField
    //! @{
    ESdpType Type() const override;
    //! @}

    //! @name Overrides from #ISdpRtpMap
    //! @{
    unsigned char PayloadType() const override;

    void PayloadType(unsigned char) override;

    const char* EncodingName() const override;

    void EncodingName(const char*) override;

    unsigned short ClockRate() const override;

    void ClockRate(unsigned short) override;

    const char* Parameters() const override;

    void Parameters(const char*) override;
    //! @}
 
    //! @name Overrides from #IField
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
};

#endif