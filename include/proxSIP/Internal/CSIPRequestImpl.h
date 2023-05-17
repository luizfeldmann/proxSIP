#ifndef _CSIPREQUESTIMPL_H_
#define _CSIPREQUESTIMPL_H_

#include "ISIPRequest.h"
#include "TSIPMessageImpl.h"
#include "CSipURIImpl.h"

//! Internal implementation of #ISIPRequest
class CSIPRequestImpl : public TSIPMessageImpl<ISIPRequest>
{
protected:
    //! Verb of the request
    ESipMethod m_eMethod;

    //! Requested URI
    CSipURIImpl m_cURI;

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
    void Assign(const ISIPRequest&) override;

    ESipMethod Method() const override;

    void Method(ESipMethod) override;

    const ISipURI& URI() const override;

    ISipURI& URI() override;
    //! @}
};

#endif