#ifndef _IUDPPROXYMSGHANDLER_H_
#define _IUDPPROXYMSGHANDLER_H_

//! Handles messages intercepted by the UDP proxy
class IUdpProxyMsgHandler
{
public:
    virtual ~IUdpProxyMsgHandler() = default;

    //! Callback when a message is sniffed
    virtual void OnMessage(const char*, size_t) = 0;
};

#endif