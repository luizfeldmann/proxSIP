#ifndef _CSIPSERVERIMPL_H_
#define _CSIPSERVERIMPL_H_

#include "ISipRequestHandler.h"
#include "ISipResponseHandler.h"
#include "ISipMessageSender.h"
#include "IAuthValidator.h"

//! Internal implementation of a basic SIP server
class CSipServerImpl : public ISipRequestHandler, public ISipResponseHandler
{
private:
    ISipMessageSender* m_pSender;
    IAuthValidator* m_pAuth;

public:
    CSipServerImpl();

    void SetAuth(IAuthValidator* pAuth);
    void SetSender(ISipMessageSender* pSender);
    void OnRequest(const ISIPRequest&) override;
    void OnResponse(const ISIPResponse&) override;
};

#endif