#include "CAsioUdpServer.h"
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>

/* CAsioUdpServerImpl */

class CAsioUdpServerImpl : public IEndpoint
{
private:
    //! Stores the transferred message
    std::array<char, 65535> m_buffer;

    //! IP of the message sender
    boost::asio::ip::udp::endpoint m_sender;

    //! Async handler from when the message is received
    void OnReceived(const boost::system::error_code& recv_error, std::size_t bytes_transferred)
    {
        bool bContinue = true;

        if (!recv_error)
        {
            if (m_pHandler)
            {
                auto szFromAddr = m_sender.address().to_string();
                m_pHandler->OnMessage(m_buffer.data(), bytes_transferred, szFromAddr.c_str(), m_sender.port());
            }
        }
        else
        {
            BOOST_LOG_TRIVIAL(error) << recv_error.message();

            // Check if error is fatal
            //if (recv_error == ...)
            //{
            //    bContinue = false;
            //}
        }

        // If no error, or if error is not fatal, continue receiving
        if (bContinue)
        {
            Listen();
        }
    }

public:
    //! IO queue
    boost::asio::io_context m_context;

    //! Local bound endpoint
    boost::asio::ip::udp::endpoint m_endpoint;

    //! The IP address returned by "Address() const"
    mutable std::string m_strEndpointAddr;

    //! Local socket
    boost::asio::ip::udp::socket m_socket;
    
    //! Object to handle the messages
    IUdpMessageHandler* m_pHandler;

    CAsioUdpServerImpl()
        : m_buffer{0}
        , m_socket(m_context)
        , m_pHandler(nullptr)
    {

    }

    //! Listens for incoming messages
    void Listen()
    {
        m_socket.async_receive_from(boost::asio::buffer(m_buffer), m_sender, boost::bind(&CAsioUdpServerImpl::OnReceived, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }

    void Address(const char* szAddr)
    {
        m_endpoint.address(boost::asio::ip::address_v4::from_string(szAddr));
    }

    const char* Address() const
    {
        m_strEndpointAddr = m_endpoint.address().to_string();
        return m_strEndpointAddr.c_str();
    }

    void Port(unsigned short usPort)
    {
        m_endpoint.port(usPort);
    }

    unsigned short Port() const
    {
        return m_endpoint.port();
    }

    void Assign(const char* szAddr, unsigned short usPort) override
    {
        Address(szAddr);
        Port(usPort);
    }
};

/* CAsioUdpServer */

CAsioUdpServer::CAsioUdpServer()
    : m_pImpl(new CAsioUdpServerImpl)
{

}

CAsioUdpServer::~CAsioUdpServer()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

IEndpoint& CAsioUdpServer::LocalEndpoint()
{
    return *m_pImpl;
}

const IEndpoint& CAsioUdpServer::LocalEndpoint() const
{
    return *m_pImpl;
}

void CAsioUdpServer::SetHandler(IUdpMessageHandler* pHandler)
{
    m_pImpl->m_pHandler = pHandler;
}

bool CAsioUdpServer::Start()
{
    boost::system::error_code ec;

    m_pImpl->m_socket.open(boost::asio::ip::udp::v4(), ec);

    if (!ec)
    {
        m_pImpl->m_socket.set_option(boost::asio::socket_base::reuse_address(true), ec);
    }

    if (!ec)
    {
        m_pImpl->m_socket.bind(m_pImpl->m_endpoint, ec);
    }

    if (!ec)
    {
        m_pImpl->Listen();
    }

    if (ec)
    {
        BOOST_LOG_TRIVIAL(error) << ec.message();
    }

    return (!ec);
}

bool CAsioUdpServer::Stop()
{
    m_pImpl->m_socket.cancel();
    return true;
}

void CAsioUdpServer::Poll()
{
    m_pImpl->m_context.poll();
}