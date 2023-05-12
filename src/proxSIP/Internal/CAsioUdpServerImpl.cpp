#include "Internal/CAsioUdpServerImpl.h"
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
    //! Instantiates a new message
    template<typename...Args>
    static auto Create(Args&&...args)
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

CAsioUdpServerImpl::CAsioUdpServerImpl()
    : m_buffer{ 0 }
    , m_socket(m_context)
    , m_pHandler(nullptr)
{

}

void CAsioUdpServerImpl::Listen()
{
    m_socket.async_receive_from(boost::asio::buffer(m_buffer), m_sender.Endpoint(),
        boost::bind(&CAsioUdpServerImpl::OnReceived, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void CAsioUdpServerImpl::OnReceived(const boost::system::error_code& recv_error, std::size_t bytes_transferred)
{
    bool bContinue = true;

    if (!recv_error)
    {
        if (m_pHandler)
        {
            m_pHandler->OnMessage(m_buffer.data(), bytes_transferred, m_sender, m_local);
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

void CAsioUdpServerImpl::OnSent(CAsioUdpSendMsgPtr, const boost::system::error_code& error, std::size_t bytes_transferred)
{
    if (error)
    {
        BOOST_LOG_TRIVIAL(error) << error.message();
    }
}

void CAsioUdpServerImpl::SendMessage(const char* pData, size_t uSize, const IEndpoint& Dst)
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

IEndpoint& CAsioUdpServerImpl::LocalEndpoint()
{
    return m_local;
}

const IEndpoint& CAsioUdpServerImpl::LocalEndpoint() const
{
    return m_local;
}

void CAsioUdpServerImpl::SetHandler(IUdpMessageHandler* pHandler)
{
    m_pHandler = pHandler;
}

bool CAsioUdpServerImpl::Start()
{
    boost::system::error_code ec;

    m_socket.open(boost::asio::ip::udp::v4(), ec);

    if (!ec)
    {
        m_socket.set_option(boost::asio::socket_base::reuse_address(true), ec);
    }

    if (!ec)
    {
        m_socket.bind(m_local.Endpoint(), ec);
    }

    if (!ec)
    {
        Listen();
    }

    if (!ec)
    {
        BOOST_LOG_TRIVIAL(info) << "Listening on " << m_local.Endpoint();
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << ec.message();
    }

    return (!ec);
}

bool CAsioUdpServerImpl::Stop()
{
    m_socket.cancel();
    return true;
}

void CAsioUdpServerImpl::Poll()
{
    m_context.poll();
}