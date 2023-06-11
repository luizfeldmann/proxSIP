#include "Internal/CSdpMediaImpl.h"
#include "Internal/snscanf.h"
#include <cinttypes>

static const char c_cSP = ' ';
static const char c_cDelim = '/';

CSdpMediaImpl::CSdpMediaImpl()
    : m_eType(ESdpMediaType::Audio)
    , m_eProtocol(ESdpMediaProto::RTPAVP)
    , m_usPort(23456)
    , m_uNumPorts(1)
{

}

/* Overrides from #ISdpMedia */

ESdpMediaType CSdpMediaImpl::MediaType() const
{
    return m_eType;
}

void CSdpMediaImpl::MediaType(ESdpMediaType eType)
{
    m_eType = eType;
}

ESdpMediaProto CSdpMediaImpl::MediaProtocol() const
{
    return m_eProtocol;
}

void CSdpMediaImpl::MediaProtocol(ESdpMediaProto eProto)
{
    m_eProtocol = eProto;
}

unsigned short CSdpMediaImpl::Port() const
{
    return m_usPort;
}

void CSdpMediaImpl::Port(unsigned short usPort)
{
    m_usPort = usPort;
}

unsigned char CSdpMediaImpl::NumPorts() const
{
    return m_uNumPorts;
}

void CSdpMediaImpl::NumPorts(unsigned char uNum)
{
    m_uNumPorts = uNum;
}

const char* CSdpMediaImpl::Formats() const
{
    return m_sFmt.c_str();
}

void CSdpMediaImpl::Formats(const char* sFmt)
{
    m_sFmt.assign(sFmt);
}

const IContainer<ISdpAttribute>& CSdpMediaImpl::Attributes() const
{
    return m_attribs;
}

IContainer<ISdpAttribute>& CSdpMediaImpl::Attributes()
{
    return m_attribs;
}

/* Overrides from #ISdpField */

ESdpType CSdpMediaImpl::Type() const
{
    return ESdpType::Media;
}

/* Overrides from #IField */

bool CSdpMediaImpl::Parse(const char* pData, size_t uSize)
{
    const char* const pEnd = pData + uSize;

    // Read the type of media
    const char* pStart = pData;

    for (;;)
    {
        if (pData >= pEnd)
            return false; /* Unexpected EOF */

        if (*pData == c_cSP)
            break;

        ++pData;
    }

    m_eType = SdpGetMediaTypeEnum(std::string(pStart, pData - pStart).c_str());
    if (ESdpMediaType::Unknown == m_eType)
        return false; /* Bad Type */

    ++pData; // Skip the SP

    // Read the port number
    pStart = pData;
    bool bNumOfPorts = false;

    for (;;)
    {
        if (pData >= pEnd)
            return false; /* Unexpected EOF */

        if (*pData == c_cSP)
            break; /* End of token */

        if (*pData == c_cDelim)
        {
            bNumOfPorts = true;
            break; /* End of token */
        }

        ++pData;
    }

    if (!_snscanf_s(pStart, pData - pStart, "%" SCNu16, &m_usPort))
        return false; /* Bad Port */

    ++pData; // Skip the SP or the '/'

    // Read the number of ports
    if (bNumOfPorts)
    {
        pStart = pData;

        for (;;)
        {
            if (pData >= pEnd)
                return false; /* Unexpected EOF */

            if (*pData == c_cSP)
                break; /* End of token */

            ++pData;
        }

        if (!_snscanf_s(pStart, pData - pStart, "%" SCNu8, &m_uNumPorts))
            return false; /* Bad number of ports */

        ++pData; // Skip the SP
    }
    else
    {
        m_uNumPorts = 1;
    }

    // Read the protocol
    pStart = pData;

    for (;;)
    {
        if (pData >= pEnd)
            return false; /* Unexpected EOF */

        if (*pData == c_cSP)
            break;

        ++pData;
    }

    m_eProtocol = SdpGetMediaProtoEnum(std::string(pStart, pData - pStart).c_str());
    if (ESdpMediaProto::Unknown == m_eProtocol)
        return false; /* Bad Protocol */

    ++pData; // Skip the SP

    // Read the formats
    m_sFmt.assign(pData, pEnd - pData);

    return true;
}

void CSdpMediaImpl::Serialize(IOutputBuffer& Buffer) const
{
    std::string sText;
    sText.reserve(_MAX_PATH);

    sText.append(SdpGetMediaTypeStr(m_eType));
    sText.append(1, c_cSP);
    sText.append(std::to_string(m_usPort));

    if (m_uNumPorts > 1)
    {
        sText.append(1, c_cDelim);
        sText.append(std::to_string(m_uNumPorts));
    }

    sText.append(1, c_cSP);
    sText.append(SdpGetMediaProtoStr(m_eProtocol));
    sText.append(1, c_cSP);
    sText.append(m_sFmt);

    Buffer.write(sText.data(), sText.size());
}