#ifndef _CCALLSESSION_H_
#define _CCALLSESSION_H_

#include "CUdpProxy.h"
#include "IEvtHandlerDTMF.h"
#include <proxSIP/CRtpMessage.h>
#include <proxSIP/CRtpPhoneEvent.h>
#include <boost/optional.hpp>

//! Manages an ongoing call
class CCallSession : public IUdpProxyMsgHandler
{
private:
    // Stores the proxies on both directions
    std::array<boost::optional<CUdpProxy>, 2> m_arrPrx;

    //! Stores the parsed RTP message
    CRtpMessage m_msgRtp;

    //! Stores the phone-event payload
    CRtpPhoneEvent m_evtDtmf;

    //! Object to handle DTMF events
    IEvtHandlerDTMF* m_pEvtHandler;

    CCallSession(const CCallSession&) = delete;
    CCallSession& operator=(const CCallSession&) = delete;

public:
    CCallSession();

    //! Handles the event queues
    void Poll();

    //! Adds a new proxy to the collection and returns the local bound port
    unsigned short AddProxy(const char* sLocalAddr, const char* sRemoteAddr, unsigned short uRemotePort);

    //! Sets handler object to be notified when DTMF event is sniffed
    void SetHandler(IEvtHandlerDTMF* pHandler);

    //! @name Overrides from #IUdpProxyMsgHandler
    //! @{
    void OnMessage(const char*, size_t) override;
    //! @}
};

#endif