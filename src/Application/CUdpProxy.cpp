#include "CUdpProxy.h"
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>

CUdpProxy::CUdpProxy(const char* sLocalAddr, const char* sRemoteAddr, unsigned short usRemotePort)
    // Zero the local buffer
    : m_buffer{ 0 }
    // Associate the socket with local context
    , m_socket{m_context}
    // Remote endpoint to specified address and port
    , m_remote(boost::asio::ip::address_v4::from_string(sRemoteAddr), usRemotePort)
    , m_pHandler(nullptr)
{
    boost::system::error_code ec;

    // Open the socket
    m_socket.open(boost::asio::ip::udp::v4(), ec);
    if (ec)
    {
        BOOST_LOG_TRIVIAL(error) << __FUNCTION__ << ec.what();
        return;
    }

    // Reuse local address
    m_socket.set_option(boost::asio::socket_base::reuse_address(true), ec);
    if (ec)
    {
        BOOST_LOG_TRIVIAL(error) << __FUNCTION__ << ec.what();
        return;
    }

    // Bind to *any* port
    boost::asio::ip::udp::endpoint edpLocal(boost::asio::ip::address_v4::from_string(sLocalAddr), 0);

    m_socket.bind(edpLocal, ec);

    if (ec)
    {
        BOOST_LOG_TRIVIAL(error) << __FUNCTION__ << ec.what();
        return;
    }

    BOOST_LOG_TRIVIAL(info) << "+PROXY: " << m_socket.local_endpoint() << " ==> " << m_remote;

    // Start listening
    Listen();
}

CUdpProxy::~CUdpProxy()
{
    m_socket.cancel();
    BOOST_LOG_TRIVIAL(info) << "-PROXY: " << m_socket.local_endpoint() << " ==> " << m_remote;
}

void CUdpProxy::Listen()
{
    m_socket.async_receive_from(boost::asio::buffer(m_buffer), m_recvfrom,
        boost::bind(&CUdpProxy::OnReceived, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void CUdpProxy::OnReceived(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    // If error, go back to listening
    if (error)
    {
        BOOST_LOG_TRIVIAL(error) << __FUNCTION__ << error.what();
        Listen();
        return;
    }

    // Treat the sniffed message
    if (m_pHandler)
        m_pHandler->OnMessage(m_buffer.data(), bytes_transferred);

    // If success, send message to remote
    m_socket.async_send_to(boost::asio::buffer(m_buffer, bytes_transferred), m_remote,
        boost::bind(&CUdpProxy::OnSent, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void CUdpProxy::OnSent(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error)
    {
        BOOST_LOG_TRIVIAL(error) << __FUNCTION__ << error.what();
    }

    // Go back to listening for the next message
    Listen();
}

void CUdpProxy::SetHandler(IUdpProxyMsgHandler* pHandler)
{
    m_pHandler = pHandler;
}

unsigned short CUdpProxy::LocalPort() const
{
    return m_socket.local_endpoint().port();
}

void CUdpProxy::Poll()
{
    m_context.poll();
}