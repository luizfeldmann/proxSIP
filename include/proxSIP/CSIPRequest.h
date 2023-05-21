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

    //! @name Overrides from IMessage
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}

    //! @name Overrides from ISIPMessage
    //! @{
    void Assign(const ISIPMessage&) override;
    
    const ESIPMessageType Type() const override;

    const char* Version() const override;

    void Version(const char*) override;

    const IEndpoint& Source() const override;

    IEndpoint& Source() override;

    const IEndpoint& Destination() const override;

    IEndpoint& Destination() override;

    const IContainer<ISipVia>& Via() const override;

    IContainer<ISipVia>& Via() override;

    const ISipContact& From() const override;

    ISipContact& From() override;

    const ISipContact& To() const override;

    ISipContact& To() override;

    const IContainer<ISipContact>& Contact() const override;

    IContainer<ISipContact>& Contact() override;

    const IKeyValueCollection& Fields() const override;

    IKeyValueCollection& Fields() override;

    const char* ContentType() const override;

    void ContentType(const char*) override;

    size_t ContentLength() const override;

    void ContentLength(size_t) override;

    const IBuffer& Content() const override;

    IBuffer& Content() override;
    //! @}
     
    //! @name Overrides from ISIPRequest
    //! @{
    void Assign(const ISIPRequest&) override;
    
    ESipMethod Method() const override;

    void Method(ESipMethod) override;

    const ISipURI& URI() const override;

    ISipURI& URI() override;
    //! @}
};

#endif