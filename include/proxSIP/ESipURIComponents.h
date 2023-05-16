#ifndef _ESIPURICOMPONENTS_H_
#define _ESIPURICOMPONENTS_H_

#include "proxSIPExports.h"

//! Represents the components that make up the URI
enum class ESipURIComponents
{
    None = 0,
    Protocol = 0x01,
    User = 0x02,
    Password = 0x04,
    Host = 0x08,
    Port = 0x16,
    Parameters = 0x32,
    Headers = 0x64,
    /* Meta items */
    PUH  = Protocol | User | Host,
    PUHP = Protocol | User | Host | Port,
    All = Protocol | User | Password | Host | Port | Parameters | Headers,
};

PROXSIP_API ESipURIComponents operator|(ESipURIComponents, ESipURIComponents);
PROXSIP_API ESipURIComponents operator&(ESipURIComponents, ESipURIComponents);
PROXSIP_API ESipURIComponents operator~(ESipURIComponents);

#endif