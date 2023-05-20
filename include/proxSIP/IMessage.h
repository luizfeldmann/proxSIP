#ifndef _IMESSAGE_H_
#define _IMESSAGE_H_

#include "IOutputBuffer.h"

//! A generic message
class PROXSIP_API IMessage
{
public:
    virtual ~IMessage() = default;

    //! Parses the message
    virtual bool Parse(const char*, size_t) = 0;

    //! Serializes the message into the buffer
    virtual void Serialize(IOutputBuffer&) const = 0;
};

#endif