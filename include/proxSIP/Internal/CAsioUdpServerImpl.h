#ifndef _CASIOUDPSERVERIMPL_H_
#define _CASIOUDPSERVERIMPL_H_

#include "IUdpServer.h"
#include "Internal/TEndpoint.h"
#include <boost/asio.hpp>

#ifdef SendMessage
#undef SendMessage
#endif

class CAsioUdpSendMsg;
using CAsioUdpSendMsgPtr = std::shared_ptr<CAsioUdpSendMsg>;

//! @copydoc IUdpServer
class CAsioUdpServerImpl : public IUdpServer
{
private:
    //! IO queue
    boost::asio::io_context m_context;

    //! Local socket
    boost::asio::ip::udp::socket m_socket;

    //! Stores the transferred message
    std::array<char, 65535> m_buffer;

    //! IP of the message sender
    TEndpoint<boost::asio::ip::udp::endpoint> m_sender;

    //! Local bound endpoint
    TEndpoint<boost::asio::ip::udp::endpoint> m_local;

    //! Object to handle the messages
    IUdpMessageHandler* m_pHandler;

    //! Listens for incoming messages
    void Listen();

    //! Async handler from when the message is received
    void OnReceived(const boost::system::error_code& recv_error, std::size_t bytes_transferred);

    //! Async handler for when a message is sent
    void OnSent(CAsioUdpSendMsgPtr, const boost::system::error_code& error, std::size_t bytes_transferred);

public:
    CAsioUdpServerImpl();

    //! @name Overrides from #IUdpMessageSender
    //! @{
    void SendMessage(const char* pData, size_t uSize, const IEndpoint& Dst) override;
    //! @}
    
    //! @name Overrides from IUdpServer
    //! @{
    IEndpoint& LocalEndpoint() override;

    const IEndpoint& LocalEndpoint() const override;

    void SetHandler(IUdpMessageHandler* pHandler) override;

    bool Start() override;

    bool Stop() override;

    void Poll() override;
    //! @}
};

#endif