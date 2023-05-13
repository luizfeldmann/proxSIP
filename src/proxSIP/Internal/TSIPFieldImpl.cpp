#include "Internal/TSIPFieldImpl.h"

//! Parses a single param in format ';key=value'
static bool SipFieldParseOneParam(const char*& pData, const char* pEnd, IKeyValueCollection& Params)
{
    // Skip the separator
    if (*pData != ';')
        return false;

    ++pData;

    // Skip the spaces
    while ((pData < pEnd) && (*pData == ' '))
        ++pData;

    const char* pKeyStart = pData;
    const char* pKeyEnd = pData;

    for (;;)
    {
        if (pData >= pEnd)
        {
            // EOF without value
            pKeyEnd = pData;
            break;
        }

        if (*pData == ';')
        {
            // Key without = and without value
            pKeyEnd = pData;
            break;
        }

        if (*pData == '=')
        {
            pKeyEnd = pData;
            
            // Trim spaces before =
            while ((pKeyEnd > pKeyStart) && *(pKeyEnd - 1) == ' ')
                --pKeyEnd;

            // eat the =
            ++pData;

            break;
        }

        ++pData;
    }

    const std::string sKey(pKeyStart, pKeyEnd - pKeyStart);

    // Trim spaces after the =
    while ((pData < pEnd) && *pData == ' ')
        ++pData;

    const char* pValStart = pData;
    const char* pValEnd = pData;

    // Key value until EOF or next ;
    while ((pData < pEnd) && *pData != ';')
    {
        ++pData;

        if (*pData != ' ')
            pValEnd = pData; // This ignores the trailling spaces between the value and the ;
    }

    const std::string sVal(pValStart, pValEnd - pValStart);

    // Save the param to the collection
    Params.Insert(sKey.c_str(), sVal.c_str());
    
    return true;
}

namespace detail 
{
    bool SipFieldParseParams(const char* pData, size_t uSize, IKeyValueCollection& Params)
    {
        bool bStatus = true;
        const char* pEnd = pData + uSize;

        for (;bStatus && (pEnd > pData);)
        {
            bStatus = SipFieldParseOneParam(pData, pEnd, Params);
        }

        return bStatus;
    }

    void SipFieldSerializeParams(const IKeyValueCollection& Params, IBuffer& Buffer)
    {
        std::string sText;

        for (const auto& p = Params.StartEnumerator(); p; ++p)
        {
            const std::string sKey = p->Key();
            const std::string sVal = p->Value();

            sText += ";" + sKey;
            
            if (!sVal.empty())
                sText += "=" + sVal;
        }

        Buffer.write(sText.data(), sText.size());
    }

}; // namespace detail