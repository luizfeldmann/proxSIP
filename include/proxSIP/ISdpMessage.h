#ifndef _ISDPMESSAGE_H_
#define _ISDPMESSAGE_H_

#include "IMessage.h"

//! Represents a Session Description Protocol (SDP) message
class PROXSIP_API ISdpMessage : public IMessage
{
public:
    virtual ~ISdpMessage() = default;
};

#endif