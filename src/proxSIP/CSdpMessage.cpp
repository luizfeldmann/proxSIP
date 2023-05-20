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

unsigned char CSdpMessage::Version() const
{
    return m_pImpl->Version();
}

void CSdpMessage::Version(unsigned char uVersion)
{
    m_pImpl->Version(uVersion);
}

const ISdpOriginator& CSdpMessage::Origin() const
{
    return m_pImpl->Origin();
}

ISdpOriginator& CSdpMessage::Origin()
{
    return m_pImpl->Origin();
}

const char* CSdpMessage::Name() const
{
    return m_pImpl->Name();
}

void CSdpMessage::Name(const char* sName)
{
    m_pImpl->Name(sName);
}

const char* CSdpMessage::Info() const
{
    return m_pImpl->Info();
}

void CSdpMessage::Info(const char* sInfo)
{
    m_pImpl->Info(sInfo);
}

const char* CSdpMessage::URI() const
{
    return m_pImpl->URI();
}

void CSdpMessage::URI(const char* sUri)
{
    m_pImpl->URI(sUri);
}

const char* CSdpMessage::Email() const
{
    return m_pImpl->Email();
}

void CSdpMessage::Email(const char* sMail)
{
    m_pImpl->Email(sMail);
}

const char* CSdpMessage::Phone() const
{
    return m_pImpl->Phone();
}

void CSdpMessage::Phone(const char* sPhone)
{
    m_pImpl->Phone(sPhone);
}

const ISdpConnection& CSdpMessage::Connection() const
{
    return m_pImpl->Connection();
}

ISdpConnection& CSdpMessage::Connection()
{
    return m_pImpl->Connection();
}

const IContainer<ISdpAttribute>& CSdpMessage::Attributes() const
{
    return m_pImpl->Attributes();
}

IContainer<ISdpAttribute>& CSdpMessage::Attributes()
{
    return m_pImpl->Attributes();
}

const ISdpTime& CSdpMessage::Time() const
{
    return m_pImpl->Time();
}

ISdpTime& CSdpMessage::Time()
{
    return m_pImpl->Time();
}

const IContainer<ISdpMedia>& CSdpMessage::Media() const
{
    return m_pImpl->Media();
}

IContainer<ISdpMedia>& CSdpMessage::Media()
{
    return m_pImpl->Media();
}

/* Overrides from IMessage */

bool CSdpMessage::Parse(const char* pData, size_t uSize)
{
    return m_pImpl->Parse(pData, uSize);
}

void CSdpMessage::Serialize(IOutputBuffer& Buffer) const
{
    m_pImpl->Serialize(Buffer);
}