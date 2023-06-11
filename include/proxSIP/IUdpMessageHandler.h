#ifndef _IUDPMESSAGEHANDLER_H_
#define _IUDPMESSAGEHANDLER_H_

#include "IEndpoint.h"
#include <cstddef>

//! Handles incoming UDP messages
class PROXSIP_API IUdpMessageHandler
{
public:
    virtual ~IUdpMessageHandler() = default;

    //! Callback from when a message is received
    virtual void OnMessage(const char* pData, size_t uSize, const IEndpoint& Src, const IEndpoint& Dst) = 0;
};

#endif