#ifndef _CSDPMEDIAIMPL_H_
#define _CSDPMEDIAIMPL_H_

#include "ISdpMedia.h"
#include "CSdpAttributeImpl.h"
#include "TContainer.h"
#include <string>

//! @copydoc ISdpMedia
class CSdpMediaImpl : public ISdpMedia
{
private:
    //! Type of media described
    ESdpMediaType m_eType;

    //! Protocol of media transport
    ESdpMediaProto m_eProtocol;

    //! Port used for media
    unsigned short m_usPort;

    //! Number of ports in range
    unsigned char m_uNumPorts;

    //! Descriptor of formats
    std::string m_sFmt;

    //! Collection of media-level attributes
    TContainer<ISdpAttribute, CSdpAttributeImpl> m_attribs;

public:
    CSdpMediaImpl();

    //! @name Overrides from #ISdpMedia
    //! @{
    ESdpMediaType MediaType() const override;

    void MediaType(ESdpMediaType) override;

    ESdpMediaProto MediaProtocol() const override;

    void MediaProtocol(ESdpMediaProto) override;

    unsigned short Port() const override;

    void Port(unsigned short) override;

    unsigned char NumPorts() const override;

    void NumPorts(unsigned char) override;

    const char* Formats() const override;

    void Formats(const char*) override;

    const IContainer<ISdpAttribute>& Attributes() const override;

    IContainer<ISdpAttribute>& Attributes() override;
    //! @}

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