#include "CSipVia.h"
#include "Internal/CSipViaImpl.h"

CSipVia::CSipVia()
    : m_pImpl(new CSipViaImpl)
{

}

CSipVia::~CSipVia()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

/* Overrides from #ISipVia */

void CSipVia::Assign(const ISipVia& Copy)
{
    return m_pImpl->Assign(Copy);
}

const char* CSipVia::Version() const
{
    return m_pImpl->Version();
}

void CSipVia::Version(const char* sVersion)
{
    m_pImpl->Version();
}

const char* CSipVia::Transport() const
{
    return m_pImpl->Transport();
}

void CSipVia::Transport(const char* sTransport)
{
    m_pImpl->Transport();
}

const char* CSipVia::URI() const
{
    return m_pImpl->URI();
}

void CSipVia::URI(const char* sUri)
{
    m_pImpl->URI(sUri);
}

/* Overrides from #ISipField */

void CSipVia::Assign(const ISipField& Copy)
{
    static_cast<ISipField*>(m_pImpl)->Assign(Copy);
}

const IKeyValueCollection& CSipVia::Parameters() const
{
    return m_pImpl->Parameters();
}

IKeyValueCollection& CSipVia::Parameters()
{
    return m_pImpl->Parameters();
}

bool CSipVia::Parse(const char* pData, size_t uSize)
{
    return m_pImpl->Parse(pData, uSize);
}

void CSipVia::Serialize(IOutputBuffer& Buffer) const
{
    m_pImpl->Serialize(Buffer);
}