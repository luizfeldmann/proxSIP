#ifndef _CSDPMESSAGEIMPL_H_
#define _CSDPMESSAGEIMPL_H_

#include "ISdpMessage.h"
#include "CSdpOriginatorImpl.h"
#include "CSdpConnectionImpl.h"
#include "CSdpTimeImpl.h"
#include "CSdpMediaImpl.h"
#include "TContainer.h"
#include <boost/optional.hpp>
#include <string>

//! @copybrief ISdpMessage
class CSdpMessageImpl : public ISdpMessage
{
private:
    //! Stores the version number
    unsigned char m_uVersion;

    //! Stores the originator of the session
    CSdpOriginatorImpl m_originator;

    //! The textual session name
    std::string m_sSessionName;

    //! Free-form human-readable description of the session or the purpose
    boost::optional<std::string> m_sSessionInfo;

    //! Pointer to additional information about the session
    boost::optional<std::string> m_sSessionURI;

    //! Email contact information for the person responsible for the conference
    boost::optional<std::string> m_sEmail;

    //! Phone contact information for the person responsible for the conference
    boost::optional<std::string> m_sPhone;

    //! Connection information for the session's streams
    TContainer<ISdpConnection, CSdpConnectionImpl> m_connections;

    //! The proposed bandwidth to be used by the session or media
    //boost::optional<CSdpBandwidth> m_bandwidth;
    
    //! Specify offsets from the base time
    //boost::optional<CSdpTimezone> m_timezone;
    
    //! A simple mechanism for key exchange is provided by the key field
    //boost::optional<CSdpCryptoKey> m_cryptokey;
    
    //! Collection of session-level attributes
    TContainer<ISdpAttribute, CSdpAttributeImpl> m_attribs;

    //! Specify the start and stop times for a session
    CSdpTimeImpl m_time;

    //! Repeat times for a session
    //boost::optional<CSdpRepeatTimeImpl> m_sRepeat;

    //! Collection of media streams
    TContainer<ISdpMedia, CSdpMediaImpl> m_medias;

    //! Parses one line of the message
    bool ParseField(ESdpType, const char*, size_t);

public:
    CSdpMessageImpl();

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