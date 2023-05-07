#ifndef _CSIPMESSAGEHANDLER_H_
#define _CSIPMESSAGEHANDLER_H_

#include "IUdpMessageHandler.h"
#include "ISipRequestHandler.h"
#include "ISipResponseHandler.h"

//! Adapter between #IUdpMessageHandler and #ISipRequestHandler / #ISipResponseHandler
class PROXSIP_API CSipMessageHandler : public IUdpMessageHandler
{
private:
    ISipRequestHandler * m_pRequestHandler;
    ISipResponseHandler* m_pResponseHandler;

public:
    CSipMessageHandler();
    CSipMessageHandler(ISipRequestHandler* pRequestHandler, ISipResponseHandler* pResponseHandler);

    //! Sets the associated request handler
    void SetHandler(ISipRequestHandler*);

    //! Sets the associated response handler
    void SetHandler(ISipResponseHandler*);

    //! Reads the request handler
    ISipRequestHandler* GetRequestHandler();

    //! Reads the response handler
    ISipResponseHandler* GetResponseHandler();

    //! Forwards a UDP message to the appropriate SIP handler
    virtual void OnMessage(const char* pData, size_t uSize, const char* szFromAddr, unsigned short usFromPort) override;
};

#endif