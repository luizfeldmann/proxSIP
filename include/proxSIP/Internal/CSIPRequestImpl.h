#ifndef _CSIPREQUESTIMPL_H_
#define _CSIPREQUESTIMPL_H_

#include "ISIPRequest.h"
#include "TSIPMessageImpl.h"

//! Internal implementation of #ISIPRequest
class CSIPRequestImpl : public TSIPMessageImpl<ISIPRequest>
{
protected:
    //! Verb of the request
    ESipMethod m_eMethod;

    //! Requested URI
    std::string m_sURI;

    //! Protocol version
    std::string m_sVersion;

public:
    //! Constructs empty request
    CSIPRequestImpl();

    //! Copy-constructible
    CSIPRequestImpl(const CSIPRequestImpl&);

    //! Copy-assignable
    CSIPRequestImpl& operator=(const CSIPRequestImpl&);

    //! Move-constructible
    CSIPRequestImpl(CSIPRequestImpl&&) noexcept;

    //! Move-assignable
    CSIPRequestImpl& operator=(CSIPRequestImpl&&) noexcept;

    //! @name Overrides from ISIPMessage
    //! @{
    const ESIPMessageType Type() const override;
    //! @}

    //! @name Overrides from ISIPRequest
    //! @{
    ESipMethod Method() const override;
    void Method(ESipMethod) override;
    const char* URI() const override;
    void URI(const char*) override;
    const char* Version() const override;
    void Version(const char*) override;
    //! @}
};

#endif