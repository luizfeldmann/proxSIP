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
        m_sSessionName.assign(pData, uSize);
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
        else
            bStatus = m_medias.back().Attributes().emplace_back().Parse(pData, uSize);
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

static inline const char* get_or_null(const boost::optional<std::string>& opt)
{
    const char* szValue = nullptr;

    if (opt.has_value())
        szValue = opt.get().c_str();

    return szValue;
}

static inline void emplace_or_reset(boost::optional<std::string>& opt, const char* sValue)
{
    if (sValue)
        opt.emplace(sValue);
    else
        opt.reset();
}

/* Overrides from ISdpMessage */

unsigned char CSdpMessageImpl::Version() const
{
    return m_uVersion;
}

void CSdpMessageImpl::Version(unsigned char uVersion)
{
    m_uVersion = uVersion;
}

const ISdpOriginator& CSdpMessageImpl::Origin() const
{
    return m_originator;
}

ISdpOriginator& CSdpMessageImpl::Origin()
{
    return m_originator;
}

const char* CSdpMessageImpl::Name() const
{
    return m_sSessionName.c_str();
}

void CSdpMessageImpl::Name(const char* sName)
{
    m_sSessionName.assign(sName);
}

const char* CSdpMessageImpl::Info() const
{
    return get_or_null(m_sSessionInfo);
}

void CSdpMessageImpl::Info(const char* sInfo)
{
    emplace_or_reset(m_sSessionInfo, sInfo);
}

const char* CSdpMessageImpl::URI() const
{
    return get_or_null(m_sSessionURI);
}

void CSdpMessageImpl::URI(const char* sUri)
{
    emplace_or_reset(m_sSessionURI, sUri);
}

const char* CSdpMessageImpl::Email() const
{
    return get_or_null(m_sEmail);
}

void CSdpMessageImpl::Email(const char* sMail)
{
    emplace_or_reset(m_sEmail, sMail);
}

const char* CSdpMessageImpl::Phone() const
{
    return get_or_null(m_sPhone);
}

void CSdpMessageImpl::Phone(const char* sPhone)
{
    emplace_or_reset(m_sPhone, sPhone);
}

const ISdpConnection& CSdpMessageImpl::Connection() const
{
    return m_connection;
}

ISdpConnection& CSdpMessageImpl::Connection()
{
    return m_connection;
}

const IContainer<ISdpAttribute>& CSdpMessageImpl::Attributes() const
{
    return m_attribs;
}

IContainer<ISdpAttribute>& CSdpMessageImpl::Attributes()
{
    return m_attribs;
}

const ISdpTime& CSdpMessageImpl::Time() const
{
    return m_time;
}

ISdpTime& CSdpMessageImpl::Time()
{
    return m_time;
}

const IContainer<ISdpMedia>& CSdpMessageImpl::Media() const
{
    return m_medias;
}

IContainer<ISdpMedia>& CSdpMessageImpl::Media()
{
    return m_medias;
}

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