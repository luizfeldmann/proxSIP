#ifndef _CSIPRESPONSE_H_
#define _CSIPRESPONSE_H_

#include "ISIPResponse.h"

class CSIPResponseImpl;

//! Representation of the data on a SIP response
class PROXSIP_API CSIPResponse : public ISIPResponse
{
private:
    CSIPResponseImpl* m_pImpl;

public:
    ~CSIPResponse();
    CSIPResponse();

    //! @name Overrides from ISIPMessage
    //! @{
    const ESIPMessageType Type() const override;
    const IEndpoint& Source() const override;
    IEndpoint& Source() override;
    const IEndpoint& Destination() const override;
    IEndpoint& Destination() override;
    const IBuffer& Content() const override;
    IBuffer& Content() override;
    //! @}
};

#endif