#include "CRemoteSwitch.h"
#include <boost/log/trivial.hpp>
#include <boost/bind.hpp>
#include <boost/beast/core/detail/base64.hpp>
#include <boost/chrono.hpp>

CRemoteSwitch::CRemoteSwitch()
    : m_socket(m_io)
{
    m_request.method(boost::beast::http::verb::get);
}

void CRemoteSwitch::Connect(const std::string& sHost, unsigned short uPort)
{
    boost::system::error_code error;

    boost::asio::ip::tcp::resolver::query query(sHost, std::to_string(uPort));
    
    boost::asio::ip::tcp::resolver resolver(m_io);
    auto results = resolver.resolve(query, error);

    if (error || results.empty())
    {
        BOOST_LOG_TRIVIAL(error) << __func__ << ": cannot resolve host '" << sHost << "'";
        if (error)
            BOOST_LOG_TRIVIAL(error) << error.message();
    }
    else
    {
        m_request.set(boost::beast::http::field::host, sHost);
        m_endpoint = results.cbegin()->endpoint();

        Reconnect();
    }
}

void CRemoteSwitch::Reconnect(boost::function<void()> fnHandlerOnConnected)
{
    m_socket.async_connect(m_endpoint,
        boost::bind(&CRemoteSwitch::OnConnected, this, boost::placeholders::_1, fnHandlerOnConnected));
}

void CRemoteSwitch::OnConnected(boost::system::error_code error, boost::function<void()> fnHandlerOnConnected)
{
    if (error)
    {
        BOOST_LOG_TRIVIAL(error) << __func__ << ": failed to connect: " << error.message();
        Reconnect(fnHandlerOnConnected); // Try again
    }

    BOOST_LOG_TRIVIAL(info) << __func__ << ": connected";

    // Success - invoke handler
    if (fnHandlerOnConnected)
        fnHandlerOnConnected();
}

void CRemoteSwitch::SetTarget(const std::string& sTarget)
{
    m_request.target(sTarget);
}

void CRemoteSwitch::SetAuth(const std::string& sUser, const std::string& sPass)
{
    // Join user and pass in a pair
    const std::string sCredPair = sUser + ":" + sPass;
    
    // Convert pair to Base-64
    size_t uEncSize = boost::beast::detail::base64::encoded_size(sCredPair.size());

    std::vector<char> vEncBuf(uEncSize, 0x00);
    uEncSize = boost::beast::detail::base64::encode(vEncBuf.data(), sCredPair.data(), sCredPair.size());

    // Add auth basic digest to header fields
    std::string sAuth = "Basic ";
    sAuth.append(vEncBuf.cbegin(), std::next(vEncBuf.cbegin(), uEncSize));
    
    m_request.set(boost::beast::http::field::authorization, sAuth);
}

void CRemoteSwitch::Activate()
{
    // Handle muti-threaded case
    boost::asio::post(m_socket.get_executor(), boost::bind(&CRemoteSwitch::DoActivate, this));
}

void CRemoteSwitch::DoActivate()
{
    // Error check
    if (!m_socket.is_open())
    {
        BOOST_LOG_TRIVIAL(error) << __func__ << ": socket is not connected";
        return;
    }

    boost::beast::http::async_write(m_socket, m_request,
        boost::bind(&CRemoteSwitch::OnRequestSent, this, boost::placeholders::_1));
}

void CRemoteSwitch::OnRequestSent(boost::system::error_code error)
{
    // Error check
    if (error)
    {
        BOOST_LOG_TRIVIAL(error) << __func__ << ": failed to request: " << error.message();
        Retry();
        return;
    }

    // Read response
    m_response.clear();
    m_response.body().clear();
    boost::beast::http::async_read(
        m_socket, m_buffer, m_response,
        boost::bind(&CRemoteSwitch::OnRecvResponse, this, boost::placeholders::_1));
}

void CRemoteSwitch::OnRecvResponse(boost::system::error_code error)
{
    // Error check
    if (error)
    {
        BOOST_LOG_TRIVIAL(error) << __func__ << ": failed to get response: " << error.message();
        Retry();
        return;
    }

    // Handle response
    const auto result = m_response.result();
    if (result != boost::beast::http::status::ok && result != boost::beast::http::status::found)
    {
        BOOST_LOG_TRIVIAL(error) << __func__ << ": request failed: " << result;
    }
}

void CRemoteSwitch::Retry()
{
    // Reset the connection state
    m_socket.shutdown(boost::asio::socket_base::shutdown_type::shutdown_both);
    m_socket.close();
    m_socket = decltype(m_socket)(m_io);
    m_buffer.clear();

    // Try activation again after reconnect
    // If reconnect takes too long, do not retry the activation...
    auto deadline = boost::chrono::system_clock::now()
        + boost::chrono::seconds(2);

    auto fnRetry = [this, deadline]() -> void
    {
        // Check it's still in time window to retry
        if (boost::chrono::system_clock::now() > deadline)
        {
            BOOST_LOG_TRIVIAL(error) << "an activation retry took too long to reconnect: retry will be ignored";
            return;
        }

        Activate();
    };

    Reconnect(fnRetry);
}

void CRemoteSwitch::Poll()
{
    m_io.poll();
}
