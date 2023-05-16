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

extern PROXSIP_API const char* c_szSipParam_user;
extern PROXSIP_API const char* c_szSipParam_method;
extern PROXSIP_API const char* c_szSipParam_transport;
extern PROXSIP_API const char* c_szSipParam_maddr;
extern PROXSIP_API const char* c_szSipParam_lr;
extern PROXSIP_API const char* c_szSipParam_sip;
extern PROXSIP_API const char* c_szSipParam_sips;
extern PROXSIP_API const char* c_szSipParam_tel;
extern PROXSIP_API const char* c_szSipParam_branch;
extern PROXSIP_API const char* c_szSipParam_ttl;
extern PROXSIP_API const char* c_szSipParam_received;
extern PROXSIP_API const char* c_szSipParam_q;
extern PROXSIP_API const char* c_szSipParam_expires;
extern PROXSIP_API const char* c_szSipParam_tag;
extern PROXSIP_API const char* c_szSipParam_rport;

//! Converts a parameter enum to a string
PROXSIP_API const char* SipGetParamStr(ESipParameter);

//! Parses a string into a parameter enum
PROXSIP_API ESipParameter SipGetParamEnum(const char*);

#endif