#ifndef _ISIPREQUESTHANDLER_H_
#define _ISIPREQUESTHANDLER_H_

#include "ISIPRequest.h"

//! Handles SIP requests
class PROXSIP_API ISipRequestHandler
{
public:
    virtual ~ISipRequestHandler() = default;

    //! Callback for when a request is received
    virtual void OnRequest(ISIPRequest&) = 0;
};

#endif