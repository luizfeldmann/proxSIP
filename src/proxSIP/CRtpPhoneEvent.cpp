#include "CRtpPhoneEvent.h"
#include "Internal/CRtpPhoneEventImpl.h"

CRtpPhoneEvent::CRtpPhoneEvent()
    : m_pImpl(new CRtpPhoneEventImpl)
{

}

CRtpPhoneEvent::~CRtpPhoneEvent()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

/* Overrides from #IRtpPhoneEvent */
EPhoneEventCode CRtpPhoneEvent::EventCode() const
{
    return m_pImpl->EventCode();
}

void CRtpPhoneEvent::EventCode(EPhoneEventCode eEvt)
{
    m_pImpl->EventCode(eEvt);
}

bool CRtpPhoneEvent::End() const
{
    return m_pImpl->End();
}

void CRtpPhoneEvent::End(bool bEnd)
{
    m_pImpl->End(bEnd);
}

unsigned char CRtpPhoneEvent::Volume() const
{
    return m_pImpl->Volume();
}

void CRtpPhoneEvent::Volume(unsigned char uVol)
{
    m_pImpl->Volume(uVol);
}

unsigned short CRtpPhoneEvent::Duration() const
{
    return m_pImpl->Duration();
}

void CRtpPhoneEvent::Duration(unsigned short uDur)
{
    m_pImpl->Duration(uDur);
}

/* Overrides from #IMessage */

bool CRtpPhoneEvent::Parse(const char* pData, size_t uSize)
{
    return m_pImpl->Parse(pData, uSize);
}

void CRtpPhoneEvent::Serialize(IOutputBuffer& Buffer) const
{
    m_pImpl->Serialize(Buffer);
}
