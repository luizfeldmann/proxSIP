#include "Internal/CSdpOriginatorImpl.h"
#include "Internal/snscanf.h"
#include <cassert>

CSdpOriginatorImpl::CSdpOriginatorImpl()
    : m_sUser("-")
    , m_uSessId(0)
    , m_uSessVersion(0)
    , m_eNetType(ESdpNetType::IN)
    , m_eAddrType(ESdpAddrType::IP4)
{

}

/* Overrides from #ISdpField */
ESdpType CSdpOriginatorImpl::Type() const
{
    return ESdpType::Originator;
}

/*  Overrides from #ISdpOriginator */

const char* CSdpOriginatorImpl::User() const
{
    return m_sUser.c_str();
}

void CSdpOriginatorImpl::User(const char* sUser)
{
    m_sUser.assign(sUser);
}

unsigned int CSdpOriginatorImpl::SessionID() const
{
    return m_uSessId;
}

void CSdpOriginatorImpl::SessionID(unsigned int uID)
{
    m_uSessId = uID;
}

unsigned int CSdpOriginatorImpl::SessionVersion() const
{
    return m_uSessVersion;
}

void CSdpOriginatorImpl::SessionVersion(unsigned int uVers)
{
    m_uSessVersion = uVers;
}

ESdpNetType CSdpOriginatorImpl::NetworkType() const
{
    return m_eNetType;
}

void CSdpOriginatorImpl::NetworkType(ESdpNetType eType)
{
    m_eNetType = eType;
}

ESdpAddrType CSdpOriginatorImpl::AddressType() const
{
    return m_eAddrType;
}

void CSdpOriginatorImpl::AddressType(ESdpAddrType eType)
{
    m_eAddrType = eType;
}

const char* CSdpOriginatorImpl::Address() const
{
    return m_sAddress.c_str();
}

void CSdpOriginatorImpl::Address(const char* sAddr)
{
    m_sAddress.assign(sAddr);
}

/* Overrides from #IField */
bool CSdpOriginatorImpl::Parse(const char* pData, size_t uSize)
{
    const char* pStart = pData;
    const char* const pEnd = pData + uSize;

    enum { USER = 0, ID, VERSION, TYPENET, TYPEADDR, ADDR };

    for (unsigned int uState = USER;;)
    {
        if (uState == ADDR)
            break; /* End of state machine */

        if (pData >= pEnd)
            return false; /* Unexpected END */

        if (*pData == ' ')
        {
            switch (uState)
            {
            case USER:
                m_sUser.assign(pStart, pData - pStart);
                break;

            case ID:
                if (!_snscanf_s(pStart, pData - pStart, "%u", &m_uSessId))
                    return false; /* Bad session ID */
                break;

            case VERSION:
                if (!_snscanf_s(pStart, pData - pStart, "%u", &m_uSessVersion))
                    return false; /* Bad session version */
                break;

            case TYPENET:
                m_eNetType = SdpGetNetTypeEnum(std::string(pStart, pData - pStart).c_str());
                if (ESdpNetType::Unknown == m_eNetType)
                    return false; /* Bad network type */
                break;

            case TYPEADDR:
                m_eAddrType = SdpGetAddrTypeEnum(std::string(pStart, pData - pStart).c_str());
                if (ESdpAddrType::Unknown == m_eAddrType)
                    return false; /* Bad address type */
                break;

            default:
                assert(0 && "Unreachable");
                break;
            }

            uState++; // Go to next state
            pStart = pData + 1; // Start next token by skipping the SP
        }

        ++pData; // next char OR skip the SP
    }

    if (pData >= pEnd)
        return false; /* Unexpected END */

    m_sAddress.assign(pData, pEnd - pData);

    return true;
}

void CSdpOriginatorImpl::Serialize(IOutputBuffer& Buffer) const
{
    char szSerialize[_MAX_PATH];

    const int nPrint = snprintf(szSerialize, sizeof(szSerialize),
        "%s %u %u %s %s %s",
        m_sUser.c_str(),
        m_uSessId,
        m_uSessVersion,
        SdpGetNetTypeStr(m_eNetType),
        SdpGetAddrTypeStr(m_eAddrType),
        m_sAddress.c_str());

    if (nPrint)
        Buffer.write(szSerialize, nPrint);
}