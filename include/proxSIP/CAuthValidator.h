#ifndef _CAUTHVALIDATOR_H_
#define _CAUTHVALIDATOR_H_

#include "IAuthValidator.h"

class CAuthValidatorImpl;

//! Implements a basic #IAuthValidator
class PROXSIP_API CAuthValidator : public IAuthValidator
{
private:
    CAuthValidatorImpl* m_pImpl;

    CAuthValidator(const CAuthValidator&) = delete;
    CAuthValidator& operator=(const CAuthValidator&) = delete;

public:
    CAuthValidator();
    ~CAuthValidator();

    //! @name Overrides from IAuthValidator
    //! @{
    void SetAccounts(const IUserAccountCollection*) override;

    ESipStatusCode ValidateAuth(IAuthDigest& Digest) override;
    //! @}
};

#endif