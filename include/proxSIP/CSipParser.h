#ifndef _CSIPPARSER_H_
#define _CSIPPARSER_H_

#include "ISIPRequest.h"
#include "ISIPResponse.h"

//! Parses SIP requests and responses
class PROXSIP_API CSipParser
{
public:
    //! Parses a raw buffer into a SIP request
    static bool ParseRequest(const char* szData, size_t uSize, ISIPRequest& Request);

    //! Parses a raw buffer into a SIP response
    static bool ParseResponse(const char* szData, size_t uSize, ISIPResponse& Response);
};

#endif