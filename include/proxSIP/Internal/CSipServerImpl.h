#ifndef _CSIPSERVERIMPL_H_
#define _CSIPSERVERIMPL_H_

#include "ISipRequestHandler.h"
#include "ISipResponseHandler.h"
#include "ISipMessageSender.h"
#include "IAuthValidator.h"
#include "ISipRegistry.h"
#include <string>

//! Internal implementation of a basic SIP server
class CSipServerImpl : public ISipRequestHandler, public ISipResponseHandler
{
private:
    std::string m_sBranch;
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

    //! @copydoc CSipServer::SetAuth
    void SetAuth(IAuthValidator* pAuth);

    //! @copydoc CSipServer::SetSender
    void SetSender(ISipMessageSender* pSender);

    //! @copydoc CSipServer::SetRegistry
    void SetRegistry(ISipRegistry*);

    //! @name Overrides from #ISipRequestHandler
    //! @{
    void OnRequest(ISIPRequest&) override;
    //! @}
    
    //! @name Overrides from #ISipResponseHandler
    //! @{
    void OnResponse(ISIPResponse&) override;
    //! @}
};

#endif