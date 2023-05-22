#include "Internal/CRtpMessageImpl.h"
#include <boost/endian.hpp>

CRtpMessageImpl::CRtpMessageImpl()
{

}

unsigned char CRtpMessageImpl::Version() const
{
    return m_stData.m_uVersion;
}

void CRtpMessageImpl::Version(unsigned char version)
{
    m_stData.m_uVersion = version;
}

bool CRtpMessageImpl::Padding() const
{
    return m_stData.m_bPadding;
}

void CRtpMessageImpl::Padding(bool bPadding)
{
    m_stData.m_bPadding = bPadding;
}

bool CRtpMessageImpl::Extension() const
{
    return m_stData.m_bExtension;
}

void CRtpMessageImpl::Extension(bool bExt)
{
    m_stData.m_bExtension = bExt;
}

bool CRtpMessageImpl::Marker() const
{
    return m_stData.m_bMarker;
}

void CRtpMessageImpl::Marker(bool bMarker)
{
    m_stData.m_bMarker = bMarker;
}

unsigned char CRtpMessageImpl::PayloadType() const
{
    return m_stData.m_uPayloadType;
}

void CRtpMessageImpl::PayloadType(unsigned char uType)
{
    m_stData.m_uPayloadType = uType;
}

unsigned short CRtpMessageImpl::SequenceNumber() const
{
    return m_stData.m_uSequence;
}

void CRtpMessageImpl::SequenceNumber(unsigned short uSeq)
{
    m_stData.m_uSequence = uSeq;
}

unsigned int CRtpMessageImpl::Timestamp() const
{
    return m_stData.m_uTimestamp;
}

void CRtpMessageImpl::Timestamp(unsigned int uTime)
{
    m_stData.m_uTimestamp = uTime;
}

unsigned int CRtpMessageImpl::SSRC() const
{
    return m_stData.m_SynchSource;
}

void CRtpMessageImpl::SSRC(unsigned int uSSRC)
{
    m_stData.m_SynchSource = uSSRC;
}

const IContainer<unsigned int>& CRtpMessageImpl::CSRC() const
{
    return m_vCSRC;
}

IContainer<unsigned int>& CRtpMessageImpl::CSRC()
{
    return m_vCSRC;
}

const IBuffer& CRtpMessageImpl::Payload() const
{
    return m_bufPayload;
}

IBuffer& CRtpMessageImpl::Payload()
{
    return m_bufPayload;
}

bool CRtpMessageImpl::Parse(const char* pData, size_t uLen)
{
    const char* const pEnd = pData + uLen;

    // Read the fixed header fields
    if (pData + sizeof(m_stData) > pEnd)
        return false; /* Unexpected END */

    memcpy(&m_stData, pData, sizeof(m_stData));
    pData += sizeof(m_stData);

    // Handle endianness
    boost::endian::big_to_native_inplace(m_stData.m_uSequence);
    boost::endian::big_to_native_inplace(m_stData.m_uTimestamp);
    boost::endian::big_to_native_inplace(m_stData.m_SynchSource);

    if (m_stData.m_bExtension)
        return false; /* Extension not implemented */

    // Read the list of sources
    m_vCSRC.clear();
    for (size_t i = 0; i < m_stData.m_uCsrc; ++i, pData += sizeof(uint32_t))
    {
        if (pData + sizeof(uint32_t) > pEnd)
            return false; /* Unexpected EOF */

        const auto* pCSRC = reinterpret_cast<const uint32_t*>(pData);
        m_vCSRC.emplace_back() = boost::endian::big_to_native(*pCSRC);
    }

    // Read payload body
    m_bufPayload.clear();
    
    if (pEnd > pData)
        m_bufPayload.write(pData, pEnd - pData);

    return true;
}

void CRtpMessageImpl::Serialize(IOutputBuffer& Buffer) const
{
    // Handle endianness in place
    SRtpData stSerData = m_stData;

    boost::endian::big_to_native_inplace(stSerData.m_uSequence);
    boost::endian::big_to_native_inplace(stSerData.m_uTimestamp);
    boost::endian::big_to_native_inplace(stSerData.m_SynchSource);

    Buffer.write((const char*)&stSerData, sizeof(stSerData));

    // Write the CSRCs
    for (auto& CSRC = m_vCSRC.iterate(); CSRC; ++CSRC)
    {
        uint32_t uData = boost::endian::native_to_big(*CSRC);
        Buffer.write((const char*)&uData, sizeof(uData));
    }

    // Write the payload
    Buffer.write(m_bufPayload.cbegin(), m_bufPayload.size());
}