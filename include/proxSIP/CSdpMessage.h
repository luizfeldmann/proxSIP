#ifndef _CSDPMESSAGE_H_
#define _CSDPMESSAGE_H_

#include "ISdpMessage.h"

class CSdpMessageImpl;

//! Base implementation of #ISdpMessage
class PROXSIP_API CSdpMessage : public ISdpMessage
{
private:
    //! Pointer to implementation
    CSdpMessageImpl* m_pImpl;

    CSdpMessage(const CSdpMessage&) = delete;
    CSdpMessage& operator=(const CSdpMessage&) = delete;

public:
    CSdpMessage();
    ~CSdpMessage();

    //! @name Overrides from ISdpMessage
    //! @{
    unsigned char Version() const override;

    void Version(unsigned char) override;

    const ISdpOriginator& Origin() const override;

    ISdpOriginator& Origin() override;

    const char* Name() const override;

    void Name(const char*) override;

    const char* Info() const override;

    void Info(const char*) override;

    const char* URI() const override;

    void URI(const char*) override;

    const char* Email() const override;

    void Email(const char*) override;

    const char* Phone() const override;

    void Phone(const char*) override;

    const IContainer<ISdpConnection>& Connection() const override;

    IContainer<ISdpConnection>& Connection() override;

    const IContainer<ISdpAttribute>& Attributes() const override;

    IContainer<ISdpAttribute>& Attributes() override;

    const ISdpTime& Time() const override;

    ISdpTime& Time() override;

    const IContainer<ISdpMedia>& Media() const override;

    IContainer<ISdpMedia>& Media() override;
    //! @}
    
    //! @name Overrides from IMessage
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
};

#endif