#include "Internal/CSdpConnectionImpl.h"
#include <cassert>

static const char c_cSep = ' ';
static const char c_cAddrSep = '/';

CSdpConnectionImpl::CSdpConnectionImpl()
    : m_eNetType(ESdpNetType::IN)
    , m_eAddrType(ESdpAddrType::IP4)
    , m_uTTL(0)
    , m_uNumAddr(1)
{

}

/* Overrides from #ISdpField */
ESdpType CSdpConnectionImpl::Type() const
{
    return ESdpType::Connection;
}

/* Overrides from #ISdpConnection */

ESdpNetType CSdpConnectionImpl::NetworkType() const
{
    return m_eNetType;
}

void CSdpConnectionImpl::NetworkType(ESdpNetType eType)
{
    m_eNetType = eType;
}

ESdpAddrType CSdpConnectionImpl::AddressType() const
{
    return m_eAddrType;
}

void CSdpConnectionImpl::AddressType(ESdpAddrType eType)
{
    m_eAddrType = eType;
}

const char* CSdpConnectionImpl::Address() const
{
    return m_sAddress.c_str();
}

void CSdpConnectionImpl::Address(const char* sAddr)
{
    m_sAddress.assign(sAddr);
}

unsigned int CSdpConnectionImpl::TTL() const
{
    return m_uTTL;
}

void CSdpConnectionImpl::TTL(unsigned int uTtl)
{
    m_uTTL = uTtl;
}

unsigned int CSdpConnectionImpl::Count() const
{
    return m_uNumAddr;
}

void CSdpConnectionImpl::Count(unsigned int uNum)
{
    m_uNumAddr = uNum;
}

/* Overrides from #IField */

bool CSdpConnectionImpl::Parse(const char* pData, size_t uSize)
{
    const char* const pEnd = pData + uSize;
    
    // Read the net type
    const char* pStart = pData;

    for (;;)
    {
        if (pData >= pEnd)
            return false; /* Unexpected END */

        if (*pData == c_cSep)
            break;

        ++pData;
    }

    m_eNetType = SdpGetNetTypeEnum(std::string(pStart, pData - pStart).c_str());
    if (ESdpNetType::Unknown == m_eNetType)
        return false; /* Bad network type */

    ++pData; // Skip the SP

    // Read the address type
    pStart = pData;

    for (;;)
    {
        if (pData >= pEnd)
            return false; /* Unexpected END */

        if (*pData == c_cSep)
            break;

        ++pData;
    }

    m_eAddrType = SdpGetAddrTypeEnum(std::string(pStart, pData - pStart).c_str());
    if (ESdpAddrType::Unknown == m_eAddrType)
        return false; /* Bad address type */

    ++pData; // Skip the SP

    // Read the address
    pStart = pData;
    bool bTTL = false;

    for (;;)
    {
        if (pData >= pEnd)
            break;

        if (*pData == c_cAddrSep)
        {
            bTTL = true;
            break;
        }

        ++pData;
    }

    m_sAddress.assign(pStart, pData - pStart);

    // Read the TTL
    bool bNumAddr = false;

    if (bTTL)
    {
        ++pData; // Skip the '/'
        pStart = pData;

        for (;;)
        {
            if (pData >= pEnd)
                break;

            if (*pData == c_cAddrSep)
            {
                bNumAddr = true;
                break;
            }

            ++pData;
        }

        if (!_snscanf_s(pStart, pData - pStart, "%u", &m_uTTL))
            return false; /* BAD TTL */
    }
    
    if (bNumAddr)
    {
        ++pData; // Skip the '/'
        pStart = pData;

        if (!_snscanf_s(pStart, pData - pStart, "%u", &m_uNumAddr))
            return false; /* BAD Num Addresses */
    }

    return true;
}

void CSdpConnectionImpl::Serialize(IOutputBuffer& Buffer) const
{
    std::string sText;
    sText.reserve(_MAX_PATH);

    sText.append(SdpGetNetTypeStr(m_eNetType));
    sText.append(1, c_cSep);
    sText.append(SdpGetAddrTypeStr(m_eAddrType));
    sText.append(1, c_cSep);
    sText.append(m_sAddress);

    if (m_uTTL > 0)
    {
        sText.append(1, c_cAddrSep);
        sText.append(std::to_string(m_uTTL));

        if (m_uNumAddr > 1)
        {
            sText.append(1, c_cAddrSep);
            sText.append(std::to_string(m_uNumAddr));
        }
    }

    Buffer.write(sText.data(), sText.size());
}