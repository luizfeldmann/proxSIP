#include "Internal/CSipContactImpl.h"

CSipContactImpl::CSipContactImpl()
{

}

/* Overrides from #ISipContact */

const char* CSipContactImpl::Name() const
{
    return m_sName.c_str();
}

void CSipContactImpl::Name(const char* sName)
{
    m_sName = sName;
}

const char* CSipContactImpl::URI() const
{
    return m_sURI.c_str();
}

void CSipContactImpl::URI(const char* sURI)
{
    m_sURI = sURI;
}

/* Overrides from #ISipField */

bool CSipContactImpl::Parse(const char* pData, size_t uSize)
{
    bool bQuotedName = false;
    const char* const pEnd = pData + uSize;

    // Skip white spaces
    for (; (pData < pEnd) && (*pData == ' '); ++pData);

    if (pData >= pEnd) return false; /*Unexpected end*/

    // Handle quoted display name
    if (*pData == '"')
    {
        bQuotedName = true;
        ++pData; // eat the quote
    }

    // Parse the name part
    const char* pNameStart = pData;
    const char* pNameEnd = pData;

    for (;;)
    {
        if (pData >= pEnd)
            return false; /*Unexpected end*/

        if (bQuotedName)
        {
            // The name ends in the quote
            if (*pData == '"')
            {
                pNameEnd = pData;
                ++pData; // eat the quote
                break;
            }
        }
        else
        {
            // The name ends in the < minus the optional trailling space
            if (*pData == '<')
            {
                pNameEnd = pData;

                while ((pNameEnd > pNameStart) && *(pNameEnd - 1) == ' ')
                    --pNameEnd;

                break;
            }
        }

        ++pData;
    }

    // Save the name
    m_sName = std::string(pNameStart, pNameEnd - pNameStart);

    // eat blanks between the quote and the <
    for (;;)
    {
        if (pData >= pEnd)
            return false; /*Unexpected end*/

        if (*pData == '<')
            break;

        if (*pData != ' ')
            return false; /*Unexpected character */

        ++pData;
    }

    ++pData; // eat the <

    // Read the URI
    const char* pUriStart = pData;
    const char* pUriEnd = pData;

    for (;;)
    {
        if (pData >= pEnd)
            return false; /*Unexpected end*/

        if (*pData == '>')
        {
            pUriEnd = pData;
            break;
        }

        ++pData;
    }

    // Save the URI
    m_sURI = std::string(pUriStart, pUriEnd - pUriStart);

    // Parse the additional parameters
    ++pData; // consume the >

    return TSIPFieldImpl::Parse(pData, pEnd - pData);
}

void CSipContactImpl::Serialize(IBuffer& Buffer) const
{
    std::string sText;

    if (!m_sName.empty())
    {
        sText = "\"" + m_sName + "\" ";
    }

    sText += "<" + m_sURI + ">";

    Buffer.write(sText.data(), sText.length());

    // Write the additional parameters
    TSIPFieldImpl::Serialize(Buffer);
}