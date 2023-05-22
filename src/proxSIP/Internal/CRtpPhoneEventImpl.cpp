#include "Internal/CRtpPhoneEventImpl.h"
#include <boost/endian.hpp>

CRtpPhoneEventImpl::CRtpPhoneEventImpl()
{

}

CRtpPhoneEventImpl::SPhoneEventData::SPhoneEventData()
    : m_uEvtCode(0)
    , m_uEnd(0)
    , m_uReserv(0)
    , m_uVolume(0)
    , m_uDuration(0)
{

}


/* Overrides from #IRtpPhoneEvent */

EPhoneEventCode CRtpPhoneEventImpl::EventCode() const
{
    return static_cast<EPhoneEventCode>(m_stData.m_uEvtCode);
}

void CRtpPhoneEventImpl::EventCode(EPhoneEventCode eEvt)
{
    m_stData.m_uEvtCode = static_cast<unsigned char>(eEvt);
}

bool CRtpPhoneEventImpl::End() const
{
    return m_stData.m_uEnd;
}

void CRtpPhoneEventImpl::End(bool bEnd)
{
    m_stData.m_uEnd = bEnd;
}

unsigned char CRtpPhoneEventImpl::Volume() const
{
    return m_stData.m_uVolume;
}

void CRtpPhoneEventImpl::Volume(unsigned char uVol)
{
    m_stData.m_uVolume = uVol;
}

unsigned short CRtpPhoneEventImpl::Duration() const
{
    return m_stData.m_uDuration;
}

void CRtpPhoneEventImpl::Duration(unsigned short uDur)
{
    m_stData.m_uDuration = uDur;
}

/* Overrides from #IMessage */

bool CRtpPhoneEventImpl::Parse(const char* pData, size_t uSize)
{
    if (uSize < sizeof(m_stData))
        return false;

    memcpy(&m_stData, pData, sizeof(m_stData));

    boost::endian::big_to_native_inplace(m_stData.m_uDuration);

    return true;
}

void CRtpPhoneEventImpl::Serialize(IOutputBuffer& Buffer) const
{
    SPhoneEventData stDataSnd = m_stData;
    boost::endian::native_to_big_inplace(stDataSnd.m_uDuration);

    Buffer.write((const char*)&stDataSnd, sizeof(stDataSnd));
}
