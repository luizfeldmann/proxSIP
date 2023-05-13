#ifndef _ESIPPARAMETERS_H_
#define _ESIPPARAMETERS_H_

#include "proxSIPExports.h"

//! Parameters using in SIP header fields
enum class ESipParameter
{
    Unknown = 0,
    user,
    method,
    transport,
    maddr,
    lr,
    sip,
    sips,
    tel,
    branch,
    ttl,
    received,
    q,
    expires,
    tag,
    rport,
};

//! Converts a parameter enum to a string
PROXSIP_API const char* SipGetParamStr(ESipParameter);

//! Parses a string into a parameter enum
PROXSIP_API ESipParameter SipGetParamEnum(const char*);

#endif