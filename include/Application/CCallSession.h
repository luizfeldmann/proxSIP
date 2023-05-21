#ifndef _CCALLSESSION_H_
#define _CCALLSESSION_H_

#include "CUdpProxy.h"
#include <boost/optional.hpp>

//! Manages an ongoing call
class CCallSession : public IUdpProxyMsgHandler
{
private:
    // Stores the proxies on both directions
    std::array<boost::optional<CUdpProxy>, 2> m_arrPrx;

    CCallSession(const CCallSession&) = delete;
    CCallSession& operator=(const CCallSession&) = delete;

public:
    CCallSession();

    //! Handles the event queues
    void Poll();

    //! Adds a new proxy to the collection and returns the local bound port
    unsigned short AddProxy(const char* sLocalAddr, const char* sRemoteAddr, unsigned short uRemotePort);

    //! @name Overrides from #IUdpProxyMsgHandler
    //! @{
    void OnMessage(const char*, size_t) override;
    //! @}
};

#endif