#ifndef _CSIPSERVER_H_
#define _CSIPSERVER_H_

#include "ISipRequestHandler.h"
#include "ISipResponseHandler.h"
#include "ISipMessageSender.h"
#include "ISipRegistry.h"
#include "IAuthValidator.h"

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

    //! Sets the authentication validator object used by this server
    void SetAuth(IAuthValidator*);

    //! Sets the message sender object for this server
    void SetSender(ISipMessageSender*);

    //! Sets the registry used by this server
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