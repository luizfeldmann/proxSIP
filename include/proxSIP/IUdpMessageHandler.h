#ifndef _IUDPMESSAGEHANDLER_H_
#define _IUDPMESSAGEHANDLER_H_

#include "proxSIPExports.h"

//! Handles incoming UDP messages
class PROXSIP_API IUdpMessageHandler
{
public:
    virtual ~IUdpMessageHandler() = default;

    //! Callback from when a message is received
    virtual void OnMessage(const char* pData, size_t uSize, const char* szFromAddr, unsigned short usFromPort) = 0;
};

#endif