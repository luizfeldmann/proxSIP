#ifndef _TENDPOINT_H_
#define _TENDPOINT_H_

#include <IEndpoint.h>
#include <string>

//! Wraps one of boost's endpoints using the #IEndpoint interface
template<typename T>
class TEndpoint : public IEndpoint
{
private:
    // The underlying endpoint object
    T m_endpoint;

    //! Stores the address string allowing it to be returned
    mutable std::string m_strEndpointAddr;

public:
    //! Construct by forwarding arguments to underlying type
    template<typename...Args>
    TEndpoint(Args&&...args)
        : m_endpoint(std::forward<Args>(args)...)
    {

    }

    //! Mutator to the underlying endpoint
    inline T& Endpoint()
    {
        return m_endpoint;
    }

    //! Accessor to the underlying endpoint
    inline const T& Endpoint() const
    {
        return m_endpoint;
    }

    //! @name Overrides from IEndpoint
    //! @{
    void Address(const char* szAddr) override
    {
        m_endpoint.address(boost::asio::ip::address_v4::from_string(szAddr));
    }

    const char* Address() const override
    {
        m_strEndpointAddr = m_endpoint.address().to_string();
        return m_strEndpointAddr.c_str();
    }

    void Port(unsigned short usPort) override
    {
        m_endpoint.port(usPort);
    }

    unsigned short Port() const override
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

#endif