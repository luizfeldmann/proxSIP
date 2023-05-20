#include "Internal/CSdpMessageImpl.h"
#include <cinttypes>

CSdpMessageImpl::CSdpMessageImpl()
    : m_uVersion(0)
{

}

bool CSdpMessageImpl::ParseField(ESdpType eType, const char* pData, size_t uSize)
{
    bool bStatus = true;

    switch (eType)
    {
    case ESdpType::Version:
        bStatus = (1 == _snscanf(pData, uSize, "%" SCNu8, &m_uVersion));
        break;

    case ESdpType::Originator:
        bStatus = m_originator.Parse(pData, uSize);
        break;

    case ESdpType::SessionName:
        m_sSessionName = std::string(pData, uSize);
        break;

    case ESdpType::Information:
        m_sSessionInfo.emplace(pData, uSize);
        break;
        
    case ESdpType::URI:
        m_sSessionURI.emplace(pData, uSize);
        break;

    case ESdpType::Email:
        m_sEmail.emplace(pData, uSize);
        break;

    case ESdpType::Phone:
        m_sPhone.emplace(pData, uSize);
        break;

    case ESdpType::Connection:
        bStatus = m_connection.Parse(pData, uSize);
        break;

    //case ESdpType::Bandwidth:
    //  bStatus = m_bandwidth.Parse(pData, uSize);
    //    break;

    //case ESdpType::TimeZone:
    //  bStatus = m_timezone.Parse(pData, uSize);
    //    break;

    //case ESdpType::Key:
    //  bStatus = m_cryptokey.Parse(pData, uSize);
    //    break;

    case ESdpType::Attribute:
        if (m_medias.empty())
            bStatus = m_attribs.emplace_back().Parse(pData, uSize);
        break;

    case ESdpType::Time:
        bStatus = m_time.Parse(pData, uSize);
        break;

    //case ESdpType::Repeat:
    //    break;

    case ESdpType::Media:
        bStatus = m_medias.emplace_back().Parse(pData, uSize);
        break;

    default:
        break;
    }

    return bStatus;
}

/* Overrides from ISdpMessage */

/* Overrides from IMessage */

bool CSdpMessageImpl::Parse(const char* pData, size_t uSize)
{
    const char* const pEnd = pData + uSize;

    for (;;)
    {
        if (pData + 2 > pEnd)
            return false; /* Unexpected end */
        
        if (pData[0] == '\r' && pData[1] == '\n')
            return true; /* End of message */

        if (pData[1] != '=')
            return false; /* Bad field type descriptor */

        // Read the field type
        const ESdpType eType = static_cast<ESdpType>(*pData);
        pData += 2; // skip 'x='

        // Read until CRLF
        const char* pFieldStart = pData;

        for (;;)
        {
            if (pData + 2 >= pEnd)
                return false; /* Unexpected end */

            if (pData[0] == '\r')
            {
                if (pData[1] != '\n')
                    return false; /* Bad line ending */

                break; /* End of field value */
            }

            ++pData;
        }

        // Handle the field
        if (!ParseField(eType, pFieldStart, pData - pFieldStart))
            return false; /* Invalid data in one of the fields */

        pData += 2; // Skip the CRLF
    }

    /* Unrechable */
}

void CSdpMessageImpl::Serialize(IOutputBuffer&) const
{

}