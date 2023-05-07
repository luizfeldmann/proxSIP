#ifndef _ISIPRESPONSE_H_
#define _ISIPRESPONSE_H_

#include "ISIPMessage.h"

//! Representation of the data on a SIP response
class PROXSIP_API ISIPResponse : public ISIPMessage
{
public:
    virtual ~ISIPResponse() = default;
};

#endif