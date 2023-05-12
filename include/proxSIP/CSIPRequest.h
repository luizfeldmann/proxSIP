#ifndef _CSIPREQUEST_H_
#define _CSIPREQUEST_H_

#include "ISIPRequest.h"

class CSIPRequestImpl;

//! Representation of the data of a SIP request
class PROXSIP_API CSIPRequest : public ISIPRequest
{
private:
    CSIPRequestImpl* m_pImpl;

    CSIPRequest(const CSIPRequest&) = delete;
    CSIPRequest& operator=(const CSIPRequest&) = delete;

public:
    ~CSIPRequest();
    CSIPRequest();

    //! @name Overrides from ISIPMessage
    //! @{
    const ESIPMessageType Type() const override;

    const char* Version() const override;

    void Version(const char*) override;

    const IEndpoint& Source() const override;

    IEndpoint& Source() override;

    const IEndpoint& Destination() const override;

    IEndpoint& Destination() override;

    const IKeyValueCollection& Fields() const override;

    IKeyValueCollection& Fields() override;

    const IBuffer& Content() const override;

    IBuffer& Content() override;
    //! @}
     
    //! @name Overrides from ISIPRequest
    //! @{
    ESipMethod Method() const override;

    void Method(ESipMethod) override;

    const char* URI() const override;

    void URI(const char*) override;
    //! @}
};

#endif