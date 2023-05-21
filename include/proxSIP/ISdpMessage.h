#ifndef _ISDPMESSAGE_H_
#define _ISDPMESSAGE_H_

#include "IMessage.h"
#include "ISdpOriginator.h"
#include "ISdpConnection.h"
#include "ISdpMedia.h"
#include "ISdpTime.h"

//! Represents a Session Description Protocol (SDP) message
class PROXSIP_API ISdpMessage : public IMessage
{
public:
    virtual ~ISdpMessage() = default;

    //! Reads the protocol version
    virtual unsigned char Version() const = 0;

    //! Sets the protocol version
    virtual void Version(unsigned char) = 0;

    //! Accessor to originator information
    virtual const ISdpOriginator& Origin() const = 0;

    //! Mutator to originator information
    virtual ISdpOriginator& Origin() = 0;

    //! Reads session name
    virtual const char* Name() const = 0;

    //! Sets the session name
    virtual void Name(const char*) = 0;

    //! Reads session information
    virtual const char* Info() const = 0;

    //! Sets the session information
    virtual void Info(const char*) = 0;

    //! Read session URI
    virtual const char* URI() const = 0;

    //! Sets session URI
    virtual void URI(const char*) = 0;

    //! Read contact e-mail address
    virtual const char* Email() const = 0;

    //! Set contact e-mail address
    virtual void Email(const char*) = 0;

    //! Read contact phone number
    virtual const char* Phone() const = 0;

    //! Set contact phone number
    virtual void Phone(const char*) = 0;

    //! Accessor to connection information
    virtual const IContainer<ISdpConnection>& Connection() const = 0;

    //! Mutator to connection information
    virtual IContainer<ISdpConnection>& Connection() = 0;

    //! Accessor to the collection of session-level attributes
    virtual const IContainer<ISdpAttribute>& Attributes() const = 0;

    //! Mutator to the collection of session-level attributes
    virtual IContainer<ISdpAttribute>& Attributes() = 0;

    //! Accessor to time information
    virtual const ISdpTime& Time() const = 0;

    //! Mutator to time information
    virtual ISdpTime& Time() = 0;

    //! Accessor to the collection of medias
    virtual const IContainer<ISdpMedia>& Media() const = 0;

    //! Mutator to the collection of medias
    virtual IContainer<ISdpMedia>& Media() = 0;
};

#endif