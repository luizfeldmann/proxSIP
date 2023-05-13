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

public:
    CSipServerImpl();

    void SetAuth(IAuthValidator* pAuth);
    void SetSender(ISipMessageSender* pSender);
    void SetRegistry(ISipRegistry*);
    void OnRequest(ISIPRequest&) override;
    void OnResponse(ISIPResponse&) override;
};

#endif