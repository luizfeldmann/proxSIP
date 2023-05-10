#ifndef _ESIPMETHODS_H_
#define _ESIPMETHODS_H_

#include "proxSIPExports.h"

//! Verbs for SIP requests
enum class ESipMethod
{
    Unknown = 0,
    REGISTER,    //!< For registering contact information
    INVITE,
    ACK,
    CANCEL,
    BYE,        //!< For terminating sessions
    OPTIONS,    //!< For querying servers about their capabilities
};

//! Converts a method to a string
PROXSIP_API const char* GetSipMethodStr(ESipMethod);

//! Parses a string into a method
PROXSIP_API ESipMethod GetSipMethodEnum(const char*);

#endif