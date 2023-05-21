#include "Internal/CSdpRtpMapImpl.h"
#include <cinttypes>

static const char c_cSP = ' ';
static const char c_cDelim = '/';

CSdpRtpMapImpl::CSdpRtpMapImpl()
    : m_uPayloadType(0)
    , m_uClockRate(8000)
{

}

/* Overrides from #ISdpField */

ESdpType CSdpRtpMapImpl::Type() const
{
    return ESdpType::Attribute;
}

/* Overrides from #ISdpRtpMap */

unsigned char CSdpRtpMapImpl::PayloadType() const
{
    return m_uPayloadType;
}

void CSdpRtpMapImpl::PayloadType(unsigned char uPayloadType)
{
    m_uPayloadType = uPayloadType;
}

const char* CSdpRtpMapImpl::EncodingName() const
{
    return m_sEncodingName.c_str();
}

void CSdpRtpMapImpl::EncodingName(const char* sEncodingName)
{
    m_sEncodingName.assign(sEncodingName);
}

unsigned short CSdpRtpMapImpl::ClockRate() const
{
    return m_uClockRate;
}

void CSdpRtpMapImpl::ClockRate(unsigned short uClockRate)
{
    m_uClockRate = uClockRate;
}

const char* CSdpRtpMapImpl::Parameters() const
{
    return m_sParameters.c_str();
}

void CSdpRtpMapImpl::Parameters(const char* sParameters)
{
    m_sParameters.assign(sParameters);
}

/* Overrides from #IField */

bool CSdpRtpMapImpl::Parse(const char* pData, size_t uSize)
{
    const char* pStart = pData;
    const char* const pEnd = pData + uSize;

    // Read payload type
    for (;;)
    {
        if (pData >= pEnd)
            return false; /* Unexpected END */

        if (*pData == c_cSP)
            break;

        ++pData;
    }

    if (!_snscanf_s(pStart, pData - pStart, "%" SCNu8, &m_uPayloadType))
        return false; /* Bad payload type */

    ++pData; // Skip the SP

    // Read the encoding name
    pStart = pData;
    for (;;)
    {
        if (pData >= pEnd)
            return false; /* Unexpected END */

        if (*pData == c_cDelim)
            break;

        ++pData;
    }

    m_sEncodingName.assign(pStart, pData - pStart);
    ++pData; // Skip the '/'

    // Read the clock rate
    pStart = pData;
    bool bParams = false;

    for (;;)
    {
        if (pData >= pEnd)
            break; // EOF without params

        if (*pData == c_cDelim)
        {
            bParams = true; // continues with params
            break;
        }

        ++pData;
    }

    if (!_snscanf_s(pStart, pData - pStart, "%" SCNu16, &m_uClockRate))
        return false; /* Bad clock */

    if (bParams)
    {
        pStart = ++pData; // Skip the '/'
        m_sEncodingName.assign(pStart, pEnd - pStart);
    }

    return true;
}

void CSdpRtpMapImpl::Serialize(IOutputBuffer& Buffer) const
{
    std::string sText;
    
    sText.append(std::to_string(m_uPayloadType));
    sText.append(1, c_cSP);
    sText.append(m_sEncodingName);
    sText.append(1, c_cDelim);
    sText.append(std::to_string(m_uClockRate));

    if (!m_sParameters.empty())
    {
        sText.append(1, c_cDelim);
        sText.append(m_sParameters);
    }

    Buffer.write(sText.data(), sText.size());
}