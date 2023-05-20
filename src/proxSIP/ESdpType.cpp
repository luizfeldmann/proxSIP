#include "ESdpType.h"
#include <cstring>

const char* c_szSdpIN = "IN";
const char* c_szSdpIP4 = "IP4";
const char* c_szSdpIP6 = "IP6";

ESdpNetType SdpGetNetTypeEnum(const char* sText)
{
    ESdpNetType eVal = ESdpNetType::Unknown;

    if (0 == strcmp(sText, c_szSdpIN))
        eVal = ESdpNetType::IN;

    return eVal;
}

const char* SdpGetNetTypeStr(ESdpNetType eVal)
{
    const char* sText = nullptr;

    switch (eVal)
    {
    default:
    case ESdpNetType::Unknown:
        break;

    case ESdpNetType::IN:
        sText = c_szSdpIN;
        break;
    }

    return sText;
}

ESdpAddrType SdpGetAddrTypeEnum(const char* sText)
{
    ESdpAddrType eVal = ESdpAddrType::Unknown;

    if (0 == strcmp(sText, c_szSdpIP4))
        eVal = ESdpAddrType::IP4;
    else if (0 == strcmp(sText, c_szSdpIP6))
        eVal = ESdpAddrType::IP6;

    return eVal;
}

const char* SdpGetAddrTypeStr(ESdpAddrType eVal)
{
    const char* sText = nullptr;

    switch (eVal)
    {
    default:
    case ESdpAddrType::Unknown:
        break;

    case ESdpAddrType::IP4:
        sText = c_szSdpIP4;
        break;

    case ESdpAddrType::IP6:
        sText = c_szSdpIP6;
        break;
    }

    return sText;
}