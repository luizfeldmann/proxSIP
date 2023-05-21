#ifndef _CUDPPROXY_H_
#define _CUDPPROXY_H_

#include <boost/asio.hpp>
#include "IUdpProxyMsgHandler.h"

//! Receives UDP messages and forwards them
class CUdpProxy
{
private:
    //! Processing context
    boost::asio::io_context m_context;

    //! Local socket
    boost::asio::ip::udp::socket m_socket;

    //! Stores the transferred message
    std::array<char, 65535> m_buffer;

    //! Address where the message will be forwarded
    boost::asio::ip::udp::endpoint m_remote;

    //! Address where the message came from
    boost::asio::ip::udp::endpoint m_recvfrom;

    IUdpProxyMsgHandler* m_pHandler;

    //! Tries to receive message
    void Listen();

    //! Async handler from when the message is received
    void OnReceived(const boost::system::error_code& recv_error, std::size_t bytes_transferred);

    //! Async handler from when the message is sent
    void OnSent(const boost::system::error_code& error, std::size_t bytes_transferred);

    CUdpProxy(const CUdpProxy&) = delete;
    CUdpProxy& operator=(const CUdpProxy&) = delete;

public:
    CUdpProxy(const char* sLocalAddr, const char* sRemoteAddr, unsigned short usRemotePort);
    ~CUdpProxy();

    //! Sets the object to receive the intercepted messages
    void SetHandler(IUdpProxyMsgHandler*);

    //! Read the port of the local endpoint
    unsigned short LocalPort() const;

    //! Processes pending event queue
    void Poll();
};

#endif