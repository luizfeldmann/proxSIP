#ifndef _CSIPMESSAGEHANDLER_H_
#define _CSIPMESSAGEHANDLER_H_

#include "IUdpMessageHandler.h"
#include "ISipRequestHandler.h"
#include "ISipResponseHandler.h"
#include "ISipMessageSender.h"
#include "IUdpMessageSender.h"

//! Adapter between:
//! #IUdpMessageHandler -> #ISipRequestHandler / #ISipResponseHandler
//! #ISipMessageSender -> #IUdpMessageSender
class PROXSIP_API CSipMessageHandler : public IUdpMessageHandler, public ISipMessageSender
{
private:
    ISipRequestHandler * m_pRequestHandler;
    ISipResponseHandler* m_pResponseHandler;
    IUdpMessageSender* m_pMessageSender;

    CSipMessageHandler(const CSipMessageHandler&) = delete;
    CSipMessageHandler& operator=(const CSipMessageHandler&) = delete;

public:
    CSipMessageHandler();

    //! Constructs with the given initial pointers to handlers
    CSipMessageHandler(ISipRequestHandler* pRequestHandler, ISipResponseHandler* pResponseHandler, IUdpMessageSender* pSender);

    //! Sets the associated request handler
    void SetHandler(ISipRequestHandler*);

    //! Sets the associated response handler
    void SetHandler(ISipResponseHandler*);

    //! Sets the associated UDP sender
    void SetSender(IUdpMessageSender*);

    //! Reads the request handler
    ISipRequestHandler* GetRequestHandler();

    //! Reads the response handler
    ISipResponseHandler* GetResponseHandler();

    //! Reads the message sender
    IUdpMessageSender* GetSender();

    //! Forwards a UDP message to the appropriate SIP handler
    virtual void OnMessage(const char* pData, size_t uSize, const IEndpoint& Src, const IEndpoint& Dst) override;

    //! Forwards a SIP message to the UDP sender
    virtual void SendMessage(const ISIPMessage&) override;
};

#endif