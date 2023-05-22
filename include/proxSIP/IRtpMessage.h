#ifndef _IRTPMESSAGE_H_
#define _IRTPMESSAGE_H_

#include "IMessage.h"
#include "IBuffer.h"
#include "IContainer.h"

//! A message in the RTP protocol
class PROXSIP_API IRtpMessage : public IMessage
{
public:
    virtual ~IRtpMessage() = default;

    //! Reads the protocol version
    virtual unsigned char Version() const = 0;

    //! Sets the protocol version
    virtual void Version(unsigned char) = 0;

    //! Reads the padding flag
    virtual bool Padding() const = 0;

    //! Sets the padding flag
    virtual void Padding(bool) = 0;

    //! Reads the extension flag
    virtual bool Extension() const = 0;

    //! Sets the extension flag
    virtual void Extension(bool) = 0;

    //! Reads the marker flag
    virtual bool Marker() const = 0;

    //! Sets the marker flag
    virtual void Marker(bool) = 0;

    //! Reads the payload type
    virtual unsigned char PayloadType() const = 0;

    //! Sets the payload type
    virtual void PayloadType(unsigned char) = 0;

    //! Reads the sequence number
    virtual unsigned short SequenceNumber() const = 0;

    //! Sets the sequence number
    virtual void SequenceNumber(unsigned short) = 0;

    //! Reads the timestamp
    virtual unsigned int Timestamp() const = 0;

    //! Sets the timestamp
    virtual void Timestamp(unsigned int) = 0;

    //! Reads the synchronization source identifier
    virtual unsigned int SSRC() const = 0;

    //! Sets the synchronization source identifier
    virtual void SSRC(unsigned int) = 0;

    //! Accessor to the collection of contributing source identifiers
    virtual const IContainer<unsigned int>& CSRC() const = 0;

    //! Mutator to the collection of contributing source identifiers
    virtual IContainer<unsigned int>& CSRC() = 0;

    //! Accessor to the payload body
    virtual const IBuffer& Payload() const = 0;

    //! Mutator to the payload body
    virtual IBuffer& Payload() = 0;
};

#endif