#ifndef _CREMOTESWITCH_H_
#define _CREMOTESWITCH_H_

#include <string>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

//! Integrates with a remote switch device
class CRemoteSwitch
{
private:
    using http_request = boost::beast::http::request<boost::beast::http::dynamic_body>;
    using http_response = boost::beast::http::response<boost::beast::http::dynamic_body>;

    boost::asio::ip::tcp::endpoint m_endpoint;  //!< Remote device
    http_request m_request;                     //!< The current transaction's HTTP request

    CRemoteSwitch(const CRemoteSwitch&) = delete;
    const CRemoteSwitch& operator=(const CRemoteSwitch&) = delete;

public:
    CRemoteSwitch();

    //! Connects to the provided endpoint
    void Connect(const std::string& sAddr, unsigned short uPort);

    //! Sets the URI for the activation request
    void SetTarget(const std::string& sTarget);

    //! Seths the authirization for the request
    void SetAuth(const std::string& sUser, const std::string& sPass);

    //! Activates the switch
    void Activate();
};

#endif