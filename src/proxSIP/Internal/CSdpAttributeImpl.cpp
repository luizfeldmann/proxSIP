#include "Internal/CSdpAttributeImpl.h"

CSdpAttributeImpl::CSdpAttributeImpl()
{

}

/* Overrides from #IKeyValuePair */

const char* CSdpAttributeImpl::Key() const
{
    return m_data.Key();
}

void CSdpAttributeImpl::Key(const char* sKey)
{
    m_data.Key(sKey);
}

const char* CSdpAttributeImpl::Value() const
{
    return m_data.Value();
}

void CSdpAttributeImpl::Value(const char* sValue)
{
    m_data.Value(sValue);
}

/* Overrides from #ISdpField */
ESdpType CSdpAttributeImpl::Type() const
{
    return ESdpType::Attribute;
}

/* Overrides from #IField */

bool CSdpAttributeImpl::Parse(const char* pData, size_t uSize)
{
    const char* const pStart = pData;
    const char* const pEnd = pData + uSize;

    for (;pData < pEnd; ++pData)
    {
        if (*pData == ':')
            break;
    }

    m_data.Key(std::string(pStart, pData - pStart).c_str());

    if (pData < pEnd)
    {
        ++pData; // Skip separator
        m_data.Value(std::string(pData, pEnd - pData).c_str());
    }

    return true;
}

void CSdpAttributeImpl::Serialize(IOutputBuffer& Buffer) const
{
    std::string sText;
    sText.append(m_data.Key());

    const char* sValue = m_data.Value();
    if (sValue && sValue[0] != '\0')
    {
        sText.append(1, ':');
        sText.append(m_data.Value());
    }

    Buffer.write(sText.data(), sText.size());
}