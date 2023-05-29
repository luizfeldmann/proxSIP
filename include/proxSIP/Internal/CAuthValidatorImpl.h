#ifndef _CAUTHVALIDATORIMPL_H_
#define _CAUTHVALIDATORIMPL_H_

#include "IAuthValidator.h"

//! Basic implementation of an authentication validator
class CAuthValidatorImpl : public IAuthValidator
{
protected:
    //! Pointer to the collection of accounts where the authentication will be verified
    const IUserAccountCollection* m_pAccounts;

public:
    CAuthValidatorImpl();

    //! @name Overrides from #IAuthValidator
    //! @{
    void SetAccounts(const IUserAccountCollection*) override;

    ESipStatusCode ValidateAuth(IAuthDigest& Digest) override;
    //! @}
};

#endif