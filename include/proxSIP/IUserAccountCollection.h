#ifndef _IUSERACCOUNTCOLLECTION_H_
#define _IUSERACCOUNTCOLLECTION_H_

#include "proxSIPExports.h"

//! Accessor to user account information
class PROXSIP_API IUserAccountCollection
{
public:
    virtual ~IUserAccountCollection() = default;

    //! Retrieves the stored user password
    virtual const char* GetUserPassword(const char* sDomain, const char* sUsername) const = 0;
};

#endif