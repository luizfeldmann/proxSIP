#ifndef _CSIPREQUEST_H_
#define _CSIPREQUEST_H_

#include "ISIPRequest.h"

class CSIPRequestImpl;

//! Representation of the data of a SIP request
class PROXSIP_API CSIPRequest : public ISIPRequest
{
private:
    CSIPRequestImpl* m_pImpl;

public:
    ~CSIPRequest();
    CSIPRequest();

    //! @name Overrides from ISIPMessage
    //! @{
    const ESIPMessageType Type() const override;
    const IEndpoint& Source() const override;
    IEndpoint& Source() override;
    const IEndpoint& Destination() const override;
    IEndpoint& Destination() override;
    //! @}
};

#endif