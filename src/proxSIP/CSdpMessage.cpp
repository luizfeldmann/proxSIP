#include "CSdpMessage.h"
#include "Internal/CSdpMessageImpl.h"

CSdpMessage::CSdpMessage()
    : m_pImpl(new CSdpMessageImpl)
{

}

CSdpMessage::~CSdpMessage()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

/* Overrides from ISdpMessage */


/* Overrides from IMessage */

bool CSdpMessage::Parse(const char* pData, size_t uSize)
{
    return m_pImpl->Parse(pData, uSize);
}

void CSdpMessage::Serialize(IOutputBuffer& Buffer) const
{
    m_pImpl->Serialize(Buffer);
}