#ifndef _IAUTHVALIDATOR_H_
#define _IAUTHVALIDATOR_H_

#include "IUserAccountCollection.h"

//! Validates authentication
class IAuthValidator
{
public:
    virtual ~IAuthValidator();

    //! Sets the collection where user accounts will be read from
    virtual void SetAccounts(const IUserAccountCollection*) = 0;
};

#endif