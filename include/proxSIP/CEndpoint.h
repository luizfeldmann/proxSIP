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

    CEndpoint(const IEndpoint&);
    CEndpoint(const CEndpoint&);

    CEndpoint& operator=(const IEndpoint&);
    CEndpoint& operator=(const CEndpoint&);

    CEndpoint(CEndpoint&&) noexcept;
    CEndpoint& operator=(CEndpoint&&) noexcept;

    //! @name Overrides from IEndpoint
    //! @{
    void Address(const char*) override;
    const char* Address() const override;
    void Port(unsigned short) override;
    unsigned short Port() const override;
    void Assign(const char*, unsigned short) override;
    //! @}
};

#endif