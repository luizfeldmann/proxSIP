#ifndef _ISIPRESPONSEHANDLER_H_
#define _ISIPRESPONSEHANDLER_H_

#include "ISIPResponse.h"

//! Handles SIP responses
class PROXSIP_API ISipResponseHandler
{
public:
    virtual ~ISipResponseHandler() = default;

    //! Callback when a response is received
    virtual void OnResponse(ISIPResponse&) = 0;
};

#endif