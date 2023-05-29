#ifndef _IAUTHVALIDATOR_H_
#define _IAUTHVALIDATOR_H_

#include "IUserAccountCollection.h"
#include "IAuthDigest.h"
#include "ESipStatusCode.h"

//! Validates authentication
class PROXSIP_API IAuthValidator
{
public:
    virtual ~IAuthValidator();

    //! Sets the collection where user accounts will be read from
    virtual void SetAccounts(const IUserAccountCollection*) = 0;

    //! Verifies the authentication
    //! @param[in] Digest Reference to the authentication data submitted by client
    //! @return ESipStatusCode::Ok If the authentication is valid;
    //!         Otherwise, returns the appropriate status code and **modifies** the digest with the required data
    virtual ESipStatusCode ValidateAuth(IAuthDigest& Digest) = 0;
};

#endif