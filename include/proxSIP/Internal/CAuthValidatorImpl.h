#ifndef _CAUTHVALIDATORIMPL_H_
#define _CAUTHVALIDATORIMPL_H_

#include "IAuthValidator.h"

//! Basic implementation of an authentication validator
class CAuthValidatorImpl : public IAuthValidator
{
protected:
    const IUserAccountCollection* m_pAccounts;

public:
    CAuthValidatorImpl();

    //! @name Overrides from #IAuthValidator
    //! @{
    void SetAccounts(const IUserAccountCollection*) override;

    ESipStatusCode ValidateAuth(IAuthDigest&) override;
    //! @}
};

#endif