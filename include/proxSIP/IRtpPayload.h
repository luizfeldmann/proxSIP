#ifndef _IRTPPAYLOAD_H_
#define _IRTPPAYLOAD_H_

#include "IMessage.h"

//! Represents a payload carried by the RTP protocol
class PROXSIP_API IRtpPayload : public IMessage
{
public:
    virtual ~IRtpPayload() = default;
};

#endif