#ifndef _CSIPSERVER_H_
#define _CSIPSERVER_H_

#include "ISipRequestHandler.h"
#include "ISipResponseHandler.h"
#include "ISipMessageSender.h"

class CSipServerImpl;

//! Implementation of a basic SIP server
class PROXSIP_API CSipServer : public ISipRequestHandler, public ISipResponseHandler
{
private:
    //! Pointer to implementation
    CSipServerImpl* m_pImpl;

    CSipServer(const CSipServer&) = delete;
    CSipServer& operator=(const CSipServer&) = delete;

public:
    CSipServer();
    ~CSipServer();

    void SetSender(ISipMessageSender*);
    void OnRequest(const ISIPRequest&) override;
    void OnResponse(const ISIPResponse&) override;
};

#endif