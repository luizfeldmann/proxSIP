#ifndef _CCALLSNIFFER_H_
#define _CCALLSNIFFER_H_

#include <proxSIP/ISipRequestHandler.h>
#include <proxSIP/ISipResponseHandler.h>
#include <proxSIP/ISdpMessage.h>
#include "CCallSession.h"
#include <map>
#include <memory>

//! Changes the SDP so the RTP goes via this machine
//! Hosts proxies to forward the RTP but also sniffs the packets
class CCallSniffer : public ISipRequestHandler, public ISipResponseHandler
{
private:
    //! Downstream request handler
    ISipRequestHandler* m_pRequestHandler;

    //! Downstream response handler
    ISipResponseHandler* m_pResponseHandler;
    
    //! Maps Call-ID to session state
    std::map<std::string, std::unique_ptr<CCallSession>> m_mSessions;

    //! Changes the address in the SDP so the RTP passes via the local PC
    void RewriteSDP(ISIPMessage& Message, CCallSession& Call);

    //! @copydoc RewriteSDP
    void RewriteSDP(ISIPMessage& Message, ISdpMessage& SDP, CCallSession& Call);

public:
    CCallSniffer();

    //! Sets the associated downstream request handler
    void SetHandler(ISipRequestHandler*);

    //! Sets the associated downstream response handler
    void SetHandler(ISipResponseHandler*);

    //! Handles the event queue
    void Poll();

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