#include "CRtpMessage.h"
#include "Internal/CRtpMessageImpl.h"

CRtpMessage::CRtpMessage()
    : m_pImpl(new CRtpMessageImpl)
{

}

CRtpMessage::~CRtpMessage()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

unsigned char CRtpMessage::Version() const
{
    return m_pImpl->Version();
}

void CRtpMessage::Version(unsigned char version)
{
    m_pImpl->Version(version);
}

bool CRtpMessage::Padding() const
{
    return m_pImpl->Padding();
}

void CRtpMessage::Padding(bool bPadding)
{
    m_pImpl->Padding(bPadding);
}

bool CRtpMessage::Extension() const
{
    return m_pImpl->Extension();
}

void CRtpMessage::Extension(bool bExt)
{
    m_pImpl->Extension(bExt);
}

bool CRtpMessage::Marker() const
{
    return m_pImpl->Marker();
}

void CRtpMessage::Marker(bool bMarker)
{
    m_pImpl->Marker(bMarker);
}

unsigned char CRtpMessage::PayloadType() const
{
    return m_pImpl->PayloadType();
}

void CRtpMessage::PayloadType(unsigned char uType)
{
    m_pImpl->PayloadType(uType);
}

unsigned short CRtpMessage::SequenceNumber() const
{
    return m_pImpl->SequenceNumber();
}

void CRtpMessage::SequenceNumber(unsigned short uSeq)
{
    m_pImpl->SequenceNumber(uSeq);
}

unsigned int CRtpMessage::Timestamp() const
{
    return m_pImpl->Timestamp();
}

void CRtpMessage::Timestamp(unsigned int uTime)
{
    m_pImpl->Timestamp(uTime);
}

unsigned int CRtpMessage::SSRC() const
{
    return m_pImpl->SSRC();
}

void CRtpMessage::SSRC(unsigned int uSSRC)
{
    m_pImpl->SSRC(uSSRC);
}

const IContainer<unsigned int>& CRtpMessage::CSRC() const
{
    return m_pImpl->CSRC();
}

IContainer<unsigned int>& CRtpMessage::CSRC()
{
    return m_pImpl->CSRC();
}

const IBuffer& CRtpMessage::Payload() const
{
    return m_pImpl->Payload();
}

IBuffer& CRtpMessage::Payload()
{
    return m_pImpl->Payload();
}

bool CRtpMessage::Parse(const char* pData, size_t uLen)
{
    return m_pImpl->Parse(pData, uLen);
}

void CRtpMessage::Serialize(IOutputBuffer& Buffer) const
{
    m_pImpl->Serialize(Buffer);
}