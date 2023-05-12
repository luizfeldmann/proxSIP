#ifndef _IUDPMESSAGESENDER_H_
#define _IUDPMESSAGESENDER_H_

#include "IEndpoint.h"

//! Sends out UDP messages
class PROXSIP_API IUdpMessageSender
{
public:
    virtual ~IUdpMessageSender() = default;

    //! Sends out a message with the given data to the provided destination
    virtual void SendMessage(const char* pData, size_t uSize, const IEndpoint& Dst) = 0;
};

#endif