#ifndef _CSIPSERVERIMPL_H_
#define _CSIPSERVERIMPL_H_

#include "ISipRequestHandler.h"
#include "ISipResponseHandler.h"
#include "ISipMessageSender.h"
#include "IAuthValidator.h"
#include "ISipRegistry.h"

//! Internal implementation of a basic SIP server
class CSipServerImpl : public ISipRequestHandler, public ISipResponseHandler
{
private:
    ISipMessageSender* m_pSender;
    IAuthValidator* m_pAuth;
    ISipRegistry* m_pRegistry;

    bool Authenticate(ISIPRequest& Request);
    void Register(ISIPRequest& Request);
    void DoRegister(ISIPResponse& Response);
    void Invite(ISIPRequest& Request);
    void Ack(ISIPRequest& Request);
    void Bye(ISIPRequest& Request);

    void Proxy(ISIPMessage&, const char* sLocation);

public:
    CSipServerImpl();

    void SetAuth(IAuthValidator* pAuth);
    void SetSender(ISipMessageSender* pSender);
    void SetRegistry(ISipRegistry*);
    void OnRequest(ISIPRequest&) override;
    void OnResponse(ISIPResponse&) override;
};

#endif