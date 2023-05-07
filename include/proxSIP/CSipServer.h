#ifndef _CSIPSERVER_H_
#define _CSIPSERVER_H_

#include "ISipRequestHandler.h"
#include "ISipResponseHandler.h"

class CSipServerImpl;

//! Implementation of a basic SIP server
class PROXSIP_API CSipServer : public ISipRequestHandler, public ISipResponseHandler
{
private:
    CSipServerImpl* m_pImpl;

public:
    CSipServer();
    ~CSipServer();

    void OnRequest(const ISIPRequest&) override;
    void OnResponse(const ISIPResponse&) override;
};

#endif