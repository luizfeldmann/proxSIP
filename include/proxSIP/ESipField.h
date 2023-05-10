#ifndef _ESIPFIELD_H_
#define _ESIPFIELD_H_

#include "proxSIPExports.h"

//! The possible data fields in SIP messages
enum class ESipField
{
    Unknown = 0,
    Via,
    MaxForwards,
    From,
    To,
    Contact,
    CallID,
    CSeq,
    Expires,
    ContentType,
    ContentLength,
};

//! Converts a field enumeration to a string
PROXSIP_API const char* GetSipFieldStr(ESipField);

#endif