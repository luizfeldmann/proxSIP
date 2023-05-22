#ifndef _CSIPRESPONSE_H_
#define _CSIPRESPONSE_H_

#include "ISIPResponse.h"

class CSIPResponseImpl;

//! Representation of the data on a SIP response
class PROXSIP_API CSIPResponse : public ISIPResponse
{
private:
    CSIPResponseImpl* m_pImpl;

    CSIPResponse(const CSIPResponse&) = delete;
    CSIPResponse& operator=(const CSIPResponse&) = delete;

public:
    ~CSIPResponse();
    CSIPResponse();

    //! @name Overrides from IMessage
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}

    //! @name Overrides from ISIPResponse
    //! @{
    void Assign(const ISIPResponse&) override;
    
    ESipStatusCode Status() const override;

    void Status(ESipStatusCode) override;
    //! @}

    //! @name Overrides from ISIPMessage
    //! @{
    void Assign(const ISIPMessage&) override;

    const ESIPMessageType Type() const override;

    const char* Version() const;

    void Version(const char*);

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

    const char* CallID() const override;

    void CallID(const char*) override;

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
};

#endif