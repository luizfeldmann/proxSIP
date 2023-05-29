#ifndef _ISIPMESSAGE_H_
#define _ISIPMESSAGE_H_

#include "IMessage.h"
#include "IEndpoint.h"
#include "IBuffer.h"
#include "ISipVia.h"
#include "ISipContact.h"
#include "IContainer.h"

//! Types of SIP messages
enum class ESIPMessageType
{
    Request,
    Response
};

//! Represents a generic message
class PROXSIP_API ISIPMessage : public IMessage
{
public:
    virtual ~ISIPMessage() = default;

    //! Assigns data (copies) from another abstract message
    virtual void Assign(const ISIPMessage&) = 0;

    //! Reads the type of this message
    virtual const ESIPMessageType Type() const = 0;

    //! Reads the protocol version
    virtual const char* Version() const = 0;

    //! Sets the protocol version
    virtual void Version(const char*) = 0;

    //! Accessor to the source endpoint of the message
    virtual const IEndpoint& Source() const = 0;

    //! Mutator to the source endpoint of the message
    virtual IEndpoint& Source() = 0;

    //! Accessor to the destination endpoint of the message
    virtual const IEndpoint& Destination() const = 0;

    //! Mutator to the destination endpoint of the message
    virtual IEndpoint& Destination() = 0;

    //! Accessor to the "Via" header fields
    virtual const IContainer<ISipVia>& Via() const = 0;

    //! Mutator to the "Via" header fields
    virtual IContainer<ISipVia>& Via() = 0;

    //! Acessor to the "From" header field
    virtual const ISipContact& From() const = 0;

    //! Mutator to the "From" header field
    virtual ISipContact& From() = 0;

    //! Acessor to the "To" header field
    virtual const ISipContact& To() const = 0;

    //! Mutator to the "To" header field
    virtual ISipContact& To() = 0;

    //! Reads the ID of the call
    virtual const char* CallID() const = 0;

    //! Sets the ID of the call
    virtual void CallID(const char*) = 0;

    //! Acessor to the "Contact" header field
    virtual const IContainer<ISipContact>& Contact() const = 0;

    //! Mutator to the "Contact" header field
    virtual IContainer<ISipContact>& Contact() = 0;

    //! Accessor to the headers
    virtual const IKeyValueCollection& Fields() const = 0;

    //! Mutator to the headers
    virtual IKeyValueCollection& Fields() = 0;

    //! Read the MIME type of the body
    virtual const char* ContentType() const = 0;

    //! Sets the MIME type of the body
    virtual void ContentType(const char*) = 0;

    //! Reads the size of the body
    virtual size_t ContentLength() const = 0;

    //! Sets the size of the body
    virtual void ContentLength(size_t) = 0;

    //! Accessor to the payload content
    virtual const IBuffer& Content() const = 0;

    //! Mutator to the payload content
    virtual IBuffer& Content() = 0;
};

#endif