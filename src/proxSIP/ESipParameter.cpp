#include "ESipParameter.h"
#include <map>
#include <string>

#define FILL_MAP(PAIR) \
    PAIR(user), \
    PAIR(method), \
    PAIR(transport), \
    PAIR(maddr), \
    PAIR(lr), \
    PAIR(sip), \
    PAIR(sips), \
    PAIR(tel), \
    PAIR(branch), \
    PAIR(ttl), \
    PAIR(received), \
    PAIR(q), \
    PAIR(expires), \
    PAIR(tag), \
    PAIR(rport), \
    // end

/* Enum to Name*/

using enum_name_map_t = std::map<ESipParameter, std::string>;
#define PAIR_ENUM_NAME(x) {ESipParameter::x, #x}

static const enum_name_map_t& GetMapEnumToName()
{
    static const enum_name_map_t theMap{
        FILL_MAP(PAIR_ENUM_NAME)
    };

    return theMap;
}

PROXSIP_API const char* SipGetParamStr(ESipParameter eEnum)
{
    const char* szName = nullptr;

    const auto& rMap = GetMapEnumToName();
    auto itFind = rMap.find(eEnum);

    if (rMap.cend() != itFind)
        szName = itFind->second.c_str();

    return szName;
}

/* Name to Enum */

using name_enum_map_t = std::map<std::string, ESipParameter>;
#define PAIR_NAME_ENUM(x) {#x, ESipParameter::x}

static const name_enum_map_t& GetMapNameToEnum()
{
    static const name_enum_map_t theMap{
        FILL_MAP(PAIR_NAME_ENUM)
    };

    return theMap;
}


PROXSIP_API ESipParameter SipGetParamEnum(const char* sName)
{
    ESipParameter eEnum = ESipParameter::Unknown;

    const auto& rMap = GetMapNameToEnum();
    auto itFind = rMap.find(sName);

    if (rMap.cend() != itFind)
        eEnum = itFind->second;

    return eEnum;
}