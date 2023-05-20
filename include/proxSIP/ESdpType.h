#ifndef _ESDPTYPE_H_
#define _ESDPTYPE_H_

#include "proxSIPExports.h"

//! Each single-character code defining data fields in SDP lines
enum class ESdpType : char
{
    Version     = 'v',
    Originator  = 'o',
    SessionName = 's',
    Information = 'i',
    URI         = 'u',
    Email       = 'e',
    Phone       = 'p',
    Connection  = 'c',
    Bandwidth   = 'b',
    TimeZone    = 'z',
    Key         = 'k',
    Attribute   = 'a',
    Time        = 't',
    Repeat      = 'r',
    Media       = 'm',
};

//! Types of network
enum class ESdpNetType
{
    Unknown = 0,
    IN, //!< Internet
};

extern PROXSIP_API const char* c_szSdpIN; //!< Text for #ESdpNetType::IN

//! Converts the text network type to the enum
PROXSIP_API ESdpNetType SdpGetNetTypeEnum(const char*);

//! Converts the enum network type to a string
PROXSIP_API const char* SdpGetNetTypeStr(ESdpNetType);

//! Types of address
enum class ESdpAddrType
{
    Unknown,
    IP4 = 4,    //!< Internet Protocol v. 4
    IP6 = 6,    //!< Internet Protocol v. 6
};

extern PROXSIP_API const char* c_szSdpIP4; //!< Text for #ESdpAddrType::IP4
extern PROXSIP_API const char* c_szSdpIP6; //!< Text for #ESdpAddrType::IP6

//! Converts the text address type to the enum
PROXSIP_API ESdpAddrType SdpGetAddrTypeEnum(const char*);

//! Converts the enum address type to a string
PROXSIP_API const char* SdpGetAddrTypeStr(ESdpAddrType);

#endif