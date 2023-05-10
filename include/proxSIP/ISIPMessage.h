#ifndef _ISIPMESSAGE_H_
#define _ISIPMESSAGE_H_

#include "IEndpoint.h"
#include "IBuffer.h"

//! Types of SIP messages
enum class ESIPMessageType
{
    Request,
    Response
};

//! Represents a generic message
class PROXSIP_API ISIPMessage
{
public:
    virtual ~ISIPMessage() = default;

    //! Reads the type of this message
    virtual const ESIPMessageType Type() const = 0;

    //! Accessor to the source endpoint of the message
    virtual const IEndpoint& Source() const = 0;

    //! Mutator to the source endpoint of the message
    virtual IEndpoint& Source() = 0;

    //! Accessor to the destination endpoint of the message
    virtual const IEndpoint& Destination() const = 0;

    //! Mutator to the destination endpoint of the message
    virtual IEndpoint& Destination() = 0;

    //! Accessor to the payload content
    virtual const IBuffer& Content() const = 0;

    //! Mutator to the payload content
    virtual IBuffer& Content() = 0;
};

#endif