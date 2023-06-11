#include "ESipParameter.h"
#include <map>
#include <string>
#include <cstring>

/* Common */

const char* c_szSipParam_user       = "user";
const char* c_szSipParam_method     = "method";
const char* c_szSipParam_transport  = "transport";
const char* c_szSipParam_maddr      = "maddr";
const char* c_szSipParam_lr         = "lr";
const char* c_szSipParam_sip        = "sip";
const char* c_szSipParam_sips       = "sips";
const char* c_szSipParam_tel        = "tel";
const char* c_szSipParam_branch     = "branch";
const char* c_szSipParam_ttl        = "ttl";
const char* c_szSipParam_received   = "received";
const char* c_szSipParam_q          = "q";
const char* c_szSipParam_expires    = "expires";
const char* c_szSipParam_tag        = "tag";
const char* c_szSipParam_rport      = "rport";

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

static const auto& GetMapEnumToName()
{
    #define PAIR_ENUM_NAME(x) {ESipParameter::x, c_szSipParam_##x}

    static const std::map<ESipParameter, const char*> theMap{
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
        szName = itFind->second;

    return szName;
}

/* Name to Enum */

static const auto& GetMapNameToEnum()
{
    struct strless {
        bool operator()(const char* a, const char* b) const {
            return std::strcmp(a, b) < 0;
        }
    };

    #define PAIR_NAME_ENUM(x) {c_szSipParam_##x, ESipParameter::x}

    static const std::map<const char*, ESipParameter, strless> theMap{
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