#include "Internal/CSdpTimeImpl.h"
#include "Internal/snscanf.h"
#include <string>
#include <cinttypes>

CSdpTimeImpl::CSdpTimeImpl()
    : m_uStartTime(0)
    , m_uEndTime(0)
{

}

/* Overrides from #ISdpField */

ESdpType CSdpTimeImpl::Type() const
{
    return ESdpType::Time;
}

/* Overrides from #ISdpTime */

unsigned long long CSdpTimeImpl::StartTime() const
{
    return m_uStartTime;
}

void CSdpTimeImpl::StartTime(unsigned long long uTime)
{
    m_uStartTime = uTime;
}

unsigned long long CSdpTimeImpl::EndTime() const
{
    return m_uEndTime;
}

void CSdpTimeImpl::EndTime(unsigned long long uTime)
{
    m_uEndTime = uTime;
}

/* Overrides from #IField */

bool CSdpTimeImpl::Parse(const char* pData, size_t uSize)
{
    return (2 == _snscanf_s(pData, uSize, "%" SCNu64 " %" SCNu64, &m_uStartTime, &m_uEndTime));
}

void CSdpTimeImpl::Serialize(IOutputBuffer& Buffer) const
{
    char szSerialize[_MAX_PATH];

    const int nPrint = snprintf(szSerialize, sizeof(szSerialize),
        "%" PRIu64 " %" PRIu64,
        m_uStartTime,
        m_uEndTime);

    if (nPrint)
        Buffer.write(szSerialize, nPrint);
}