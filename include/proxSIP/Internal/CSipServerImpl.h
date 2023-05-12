#ifndef _CSIPSERVERIMPL_H_
#define _CSIPSERVERIMPL_H_

#include "ISipRequestHandler.h"
#include "ISipResponseHandler.h"
#include "ISipMessageSender.h"

//! Internal implementation of a basic SIP server
class CSipServerImpl : public ISipRequestHandler, public ISipResponseHandler
{
private:
    ISipMessageSender* m_pSender;

public:
    CSipServerImpl();

    void SetSender(ISipMessageSender* pSender);
    void OnRequest(const ISIPRequest&) override;
    void OnResponse(const ISIPResponse&) override;
};

#endif