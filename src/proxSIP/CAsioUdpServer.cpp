#include "CAsioUdpServer.h"
#include "CEndpoint.h"
#include <boost/asio.hpp>
#include <boost/log/trivial.hpp>
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>

#ifdef SendMessage
#undef SendMessage
#endif

/* CAsioUdpSendMsg */

class CAsioUdpSendMsg : public std::enable_shared_from_this<CAsioUdpSendMsg>
{
protected:
    //! Stores the message data
    std::vector<char> m_vMsg;

    //! Internal construction of the message
    CAsioUdpSendMsg(const char* p, size_t len)
        : m_vMsg(p, p + len)
    {

    }
    

public:
    using pointer = std::shared_ptr<CAsioUdpSendMsg>;

    //! Instantiates a new message
    template<typename...Args>
    static pointer Create(Args&&...args)
    {
        struct make_shared_enabler : public CAsioUdpSendMsg
        {
            make_shared_enabler(Args&&...args)
                : CAsioUdpSendMsg(std::forward<Args>(args)...) {}
        };

        return std::make_shared<make_shared_enabler>(std::forward<Args>(args)...);
    }

    //! Retrieves a buffer
    auto buffer()
    {
        return boost::asio::buffer(m_vMsg);
    }
};

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
                CEndpoint Sender(m_sender.address().to_string().c_str(), m_sender.port());
                m_pHandler->OnMessage(m_buffer.data(), bytes_transferred, Sender, *this);
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

    //! Async handler for when a message is sent
    void OnSent(CAsioUdpSendMsg::pointer, const boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if (error)
        {
            BOOST_LOG_TRIVIAL(error) << error.message();
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
        m_socket.async_receive_from(boost::asio::buffer(m_buffer), m_sender, 
            boost::bind(&CAsioUdpServerImpl::OnReceived, this, 
                boost::asio::placeholders::error, 
                boost::asio::placeholders::bytes_transferred));
    }

    //! Sends out a message
    void SendMessage(const char* pData, size_t uSize, const IEndpoint& Dst)
    {
        auto pMsg = CAsioUdpSendMsg::Create(pData, uSize);

        const auto edpDst = boost::asio::ip::udp::endpoint(
            boost::asio::ip::address_v4::from_string(Dst.Address()),
            Dst.Port()
        );

        m_socket.async_send_to(pMsg->buffer(), edpDst, 
            boost::bind(&CAsioUdpServerImpl::OnSent, this,
                pMsg,
                boost::asio::placeholders::error, 
                boost::asio::placeholders::bytes_transferred));
    }

    //! @name Override from IEndpoint
    //! @{
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

    void Assign(const IEndpoint& other) override
    {
        Address(other.Address());
        Port(other.Port());
    }
    //! @}
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

void CAsioUdpServer::SendMessage(const char* pData, size_t uSize, const IEndpoint& Dst)
{
    m_pImpl->SendMessage(pData, uSize, Dst);
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

    if (!ec)
    {
        BOOST_LOG_TRIVIAL(info) << "Listening on " << m_pImpl->m_endpoint;
    }
    else
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