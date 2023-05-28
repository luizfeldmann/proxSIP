#ifndef _CREMOTESWITCH_H_
#define _CREMOTESWITCH_H_

#include <string>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/function.hpp>

//! Integrates with a remote switch device
class CRemoteSwitch
{
private:
    using http_request = boost::beast::http::request<boost::beast::http::dynamic_body>;
    using http_response = boost::beast::http::response<boost::beast::http::dynamic_body>;

    boost::asio::io_context m_io;               //!< Context for asynchronous operations
    boost::asio::ip::tcp::endpoint m_endpoint;  //!< Remote device
    boost::asio::ip::tcp::socket m_socket;      //!< The socket of the connection
    boost::beast::flat_buffer m_buffer;         //!< A common buffer used for I/O on this connection
    http_request m_request;                     //!< The current transaction's HTTP request
    http_response m_response;                   //!< The current transaction's HTTP response
    
    //! Activates the switch
    void DoActivate();

    //! Connects the socket again
    void Reconnect(boost::function<void()> fnHandlerOnConnected = 0);
    
    //! Attempts to reconnect and retry the activation
    void Retry();

    //! Async callback after connect attempt
    void OnConnected(boost::system::error_code error, boost::function<void()> fnHandlerOnConnected);
    
    //! Async callback after request is made
    void OnRequestSent(boost::system::error_code error);

    //! Async callback after response is received
    void OnRecvResponse(boost::system::error_code error);

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

    //! Handles the event queue
    void Poll();
};

#endif