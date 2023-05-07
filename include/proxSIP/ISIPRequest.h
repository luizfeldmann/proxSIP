#ifndef _ISIPREQUEST_H_
#define _ISIPREQUEST_H_

#include "ISIPMessage.h"

//! Representation of the data of a SIP request
class PROXSIP_API ISIPRequest : public ISIPMessage
{
public:
    virtual ~ISIPRequest() = default;

};

#endif