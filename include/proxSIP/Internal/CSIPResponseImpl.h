#ifndef _CSIPRESPONSEIMPL_H_
#define _CSIPRESPONSEIMPL_H_

#include "TSIPMessageImpl.h"
#include "ISIPResponse.h"

//! Internal implementation of #ISIPResponse
class CSIPResponseImpl : public TSIPMessageImpl<ISIPResponse>
{
protected:
    //! The status code of the response
    ESipStatusCode m_eStatus;

public:
    //! Constructs empty response
    CSIPResponseImpl();

    //! Copy-constructible
    CSIPResponseImpl(const CSIPResponseImpl&);

    //! Copy-assignable
    CSIPResponseImpl& operator=(const CSIPResponseImpl&);

    //! Move-constructible
    CSIPResponseImpl(CSIPResponseImpl&&) noexcept;

    //! Move-assignable
    CSIPResponseImpl& operator=(CSIPResponseImpl&&) noexcept;

    //! @name Overrides from ISIPMessage
    //! @{
    const ESIPMessageType Type() const override;
    //! @}
    
    //! @name Overrides from ISIPResponse
    //! @{
    void Assign(const ISIPResponse&) override;

    ESipStatusCode Status() const override;

    void Status(ESipStatusCode) override;
    //! @}
};

#endif