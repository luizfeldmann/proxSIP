#include "ESipField.h"
#include <map>
#include <string>
#include <cstring>

/* Common */

const char* c_szSipVia             = "Via";
const char* c_szSipMaxForwards     = "Max-Forwards";
const char* c_szSipFrom            = "From";
const char* c_szSipTo              = "To";
const char* c_szSipContact         = "Contact";
const char* c_szSipCallID          = "Call-ID";
const char* c_szSipCSeq            = "CSeq";
const char* c_szSipExpires         = "Expires";
const char* c_szSipContentType     = "Content-Type";
const char* c_szSipContentLength   = "Content-Length";

#define FILL_MAP(PAIR) \
    PAIR(Via), \
    PAIR(MaxForwards), \
    PAIR(From), \
    PAIR(To), \
    PAIR(Contact), \
    PAIR(CallID), \
    PAIR(CSeq), \
    PAIR(Expires), \
    PAIR(ContentType), \
    PAIR(ContentLength), \
    // end

/* Enum to Name */

static const auto& GetMapEnumToStr()
{
    #define MAP_ENUM_STR(X) { ESipField::X, c_szSip##X}

    static const std::map<ESipField, const char*> theMap {
        FILL_MAP(MAP_ENUM_STR)
    };

    return theMap;
}

const char* SipGetFieldStr(ESipField eField)
{
    const char* szName = nullptr;

    const auto& rMap = GetMapEnumToStr();
    auto itFind = rMap.find(eField);

    if (rMap.cend() != itFind)
        szName = itFind->second;

    return szName;
}

/* Name to Enum */

static const auto& GetMapStrToEnum()
{
    struct strless {
        bool operator()(const char* a, const char* b) const {
            return std::strcmp(a, b) < 0;
        }
    };

    #define MAP_STR_ENUM(X) {c_szSip##X, ESipField::X }

    static const std::map<const char*, ESipField, strless> theMap {
        FILL_MAP(MAP_STR_ENUM)
    };

    return theMap;
}

ESipField SipGetFieldEnum(const char* sName)
{
    ESipField eValue = ESipField::Unknown;

    const auto& rMap = GetMapStrToEnum();
    auto itFind = rMap.find(sName);

    if (rMap.cend() != itFind)
        eValue = itFind->second;

    return eValue;
}
