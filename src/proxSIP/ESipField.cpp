#include "ESipField.h"
#include <map>
#include <string>

/* Enum to Name */

using field_name_map_t = std::map<ESipField, std::string>;

static const field_name_map_t& GetMapFieldToName()
{
    static const field_name_map_t theMap
    {
        { ESipField::Via, "Via"},
        { ESipField::MaxForwards, "Max-Forwards"},
        { ESipField::From, "From"},
        { ESipField::To, "To"},
        { ESipField::Contact, "Contact"},
        { ESipField::CallID, "CallID"},
        { ESipField::CSeq, "CSeq"},
        { ESipField::Expires, "Expires"},
        { ESipField::ContentType, "Content-Type"},
        { ESipField::ContentLength, "Content-Length"},
    };

    return theMap;
}

const char* GetSipFieldStr(ESipField eField)
{
    const char* szField = nullptr;

    const auto& rMap = GetMapFieldToName();
    auto itFind = rMap.find(eField);

    if (rMap.cend() != itFind)
        szField = itFind->second.c_str();

    return szField;
}