#include "CRemoteSwitch.h"
#include <boost/log/trivial.hpp>
#include <boost/bind.hpp>
#include <boost/beast/core/detail/base64.hpp>
#include <boost/chrono.hpp>

CRemoteSwitch::CRemoteSwitch()
{
    m_request.method(boost::beast::http::verb::get);
}

void CRemoteSwitch::Connect(const std::string& sHost, unsigned short uPort)
{
    boost::asio::io_context io;
    boost::system::error_code error;

    boost::asio::ip::tcp::resolver::query query(sHost, std::to_string(uPort));
    
    boost::asio::ip::tcp::resolver resolver(io);
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
    }
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
    boost::system::error_code error;

    boost::asio::io_context io;
    boost::asio::ip::tcp::socket sock(io);

    // Connect the socket
    sock.connect(m_endpoint, error);

    if (error)
    {
        BOOST_LOG_TRIVIAL(error) << __func__ << ": failed to connect: " << error.message();
        return;
    }

    // Write the request
    boost::beast::http::write(sock, m_request);

    if (error)
    {
        BOOST_LOG_TRIVIAL(error) << __func__ << ": failed to request: " << error.message();
        sock.close();
        return;
    }

    // Read the response
    boost::beast::flat_buffer buffer;
    http_response response;

    boost::beast::http::read(sock, buffer, response);

    if (error)
    {
        BOOST_LOG_TRIVIAL(error) << __func__ << ": failed to get response: " << error.message();
        sock.close();
        return;
    }

    const auto result = response.result();
    if (result != boost::beast::http::status::ok && result != boost::beast::http::status::found)
    {
        BOOST_LOG_TRIVIAL(error) << __func__ << ": request failed: " << result;
    }

    sock.close();
}