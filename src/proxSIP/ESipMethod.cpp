#include "ESipMethods.h"
#include <map>
#include <string>

#define FILL_SIP_MAP(PAIR) \
    PAIR(REGISTER), \
    PAIR(INVITE), \
    PAIR(ACK), \
    PAIR(CANCEL), \
    PAIR(BYE), \
    PAIR(OPTIONS), \
    // end

/* Name to Enum */

using name_method_map_t = std::map<std::string, ESipMethod>;
#define PAIR_NAME_METHOD(x) {#x, ESipMethod::x}

const name_method_map_t& GetMapNameToMethod()
{
    static const name_method_map_t theMap {
        FILL_SIP_MAP(PAIR_NAME_METHOD)
    };

    return theMap;
}

ESipMethod GetSipMethodEnum(const char* szMethod)
{
    ESipMethod eMethod = ESipMethod::Unknown;

    const auto& rMap = GetMapNameToMethod();
    auto itFind = rMap.find(szMethod);

    if (rMap.cend() != itFind)
        eMethod = itFind->second;

    return eMethod;
}

/* Enum to Name */

using method_name_map_t = std::map<ESipMethod, std::string>;
#define PAIR_METHOD_NAME(x) {ESipMethod::x, #x}

const method_name_map_t& GetMapMethodToName()
{
    static const method_name_map_t theMap{
        FILL_SIP_MAP(PAIR_METHOD_NAME)
    };

    return theMap;
}

const char* GetSipMethodStr(ESipMethod eMethod)
{
    const char* szMethod = nullptr;

    const auto& rMap = GetMapMethodToName();
    auto itFind = rMap.find(eMethod);

    if (rMap.cend() != itFind)
        szMethod = itFind->second.c_str();

    return szMethod;
}