#include "ESipMethods.h"
#include <map>
#include <string>
#include <cstring>

const char* c_szSipMethodREGISTER = "REGISTER";
const char* c_szSipMethodINVITE   = "INVITE";
const char* c_szSipMethodACK      = "ACK";
const char* c_szSipMethodCANCEL   = "CANCEL";
const char* c_szSipMethodBYE      = "BYE";
const char* c_szSipMethodOPTIONS  = "OPTIONS";

#define FILL_SIP_MAP(PAIR) \
    PAIR(REGISTER), \
    PAIR(INVITE), \
    PAIR(ACK), \
    PAIR(CANCEL), \
    PAIR(BYE), \
    PAIR(OPTIONS), \
    // end

/* Name to Enum */
static const auto& GetMapNameToMethod()
{
    struct strless {
        bool operator()(const char* a, const char* b) const { 
            return std::strcmp(a, b) < 0;
        }
    };

    #define PAIR_NAME_METHOD(x) {c_szSipMethod##x, ESipMethod::x}

    static const std::map<const char*, ESipMethod, strless> theMap {
        FILL_SIP_MAP(PAIR_NAME_METHOD)
    };

    return theMap;
}

ESipMethod SipGetMethodEnum(const char* szMethod)
{
    ESipMethod eMethod = ESipMethod::Unknown;

    const auto& rMap = GetMapNameToMethod();
    auto itFind = rMap.find(szMethod);

    if (rMap.cend() != itFind)
        eMethod = itFind->second;

    return eMethod;
}

/* Enum to Name */

static const auto& GetMapMethodToName()
{
    #define PAIR_METHOD_NAME(x) {ESipMethod::x, c_szSipMethod##x}

    static const std::map<ESipMethod, const char*> theMap{
        FILL_SIP_MAP(PAIR_METHOD_NAME)
    };

    return theMap;
}

const char* SipGetMethodStr(ESipMethod eMethod)
{
    const char* szMethod = nullptr;

    const auto& rMap = GetMapMethodToName();
    auto itFind = rMap.find(eMethod);

    if (rMap.cend() != itFind)
        szMethod = itFind->second;

    return szMethod;
}