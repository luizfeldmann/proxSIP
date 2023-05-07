#ifndef _CENDPOINT_H_
#define _CENDPOINT_H_

#include "IEndpoint.h"

class CEndpointImpl;

//! Represents a pair of Address:Port
class PROXSIP_API CEndpoint : public IEndpoint
{
private:
    //! Internal implementation
    CEndpointImpl* m_pImpl;

public:
    ~CEndpoint();

    CEndpoint();
    CEndpoint(const char* szAddr, unsigned short uPort);

    //! Copies from an abstract #IEndpoint
    CEndpoint(const IEndpoint&);

    //! Copy-constructor
    CEndpoint(const CEndpoint&);

    //! Copy-assignment operator
    CEndpoint& operator=(const CEndpoint&);

    //! Move-constructor
    CEndpoint(CEndpoint&&) noexcept;

    //! Move-assignment operator
    CEndpoint& operator=(CEndpoint&&) noexcept;

    //! @name Overrides from IEndpoint
    //! @{
    IEndpoint& operator=(const IEndpoint&) override;
    void Address(const char*) override;
    const char* Address() const override;
    void Port(unsigned short) override;
    unsigned short Port() const override;
    void Assign(const char*, unsigned short) override;
    //! @}
};

#endif