#ifndef _CENDPOINT_H_
#define _CENDPOINT_H_

#include "IEndpoint.h"
#include "TImplPtr.h"

class CEndpointImpl;
DECLARE_PIMPL(CEndpointImpl);

//! Represents a pair of Address:Port
class PROXSIP_API CEndpoint : public TImplPtr<CEndpoint, CEndpointImpl>, public IEndpoint
{
public:
    CEndpoint();
    CEndpoint(const char* szAddr, unsigned short uPort);

    //! Copies from an abstract #IEndpoint
    CEndpoint(const IEndpoint&);

    //! @name Overrides from IEndpoint
    //! @{
    void Address(const char*) override;
    const char* Address() const override;
    void Port(unsigned short) override;
    unsigned short Port() const override;
    void Assign(const char*, unsigned short) override;
    void Assign(const IEndpoint&) override;
    //! @}
};

#endif