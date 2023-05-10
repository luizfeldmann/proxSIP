#ifndef _CENDPOINTIMPL_H_
#define _CENDPOINTIMPL_H_

#include "IEndpoint.h"
#include <string>

//! Internal implementation of #IEndpoint
class CEndpointImpl : public IEndpoint
{
protected:
    //! Stores the address
    std::string m_sAddr;

    //! Stores the port
    unsigned short m_usPort;

public:
    //! Copy-constructible
    CEndpointImpl(const CEndpointImpl&);

    //! Copy-assignable
    CEndpointImpl& operator=(const CEndpointImpl&);

    //! Move-constructible
    CEndpointImpl(CEndpointImpl&&) noexcept;

    //! Move-assignable
    CEndpointImpl& operator=(CEndpointImpl&&) noexcept;

    //! Construct using provided address and port
    CEndpointImpl(const char* szAddr = "", unsigned short usPort = 0);

    //! Construct by copying data from abstract interface
    CEndpointImpl(const IEndpoint& other);

    //! @name Overrides from #IEndpoint
    //! @{
    void Address(const char*) override;
    const char* Address() const override;
    void Assign(const char*, unsigned short) override;
    void Assign(const IEndpoint&) override;
    void Port(unsigned short) override;
    unsigned short Port() const override;
    //! @}
};

#endif