#include "Internal/CSIPRequestImpl.h"
#include "CSipParser.h"
#include "CSipSerializer.h"

CSIPRequestImpl::CSIPRequestImpl()
    : m_eMethod(ESipMethod::Unknown)
{

}

CSIPRequestImpl::CSIPRequestImpl(const CSIPRequestImpl&) = default;

CSIPRequestImpl& CSIPRequestImpl::operator=(const CSIPRequestImpl&) = default;

CSIPRequestImpl::CSIPRequestImpl(CSIPRequestImpl&&) noexcept = default;

CSIPRequestImpl& CSIPRequestImpl::operator=(CSIPRequestImpl&&) noexcept = default;

const ESIPMessageType CSIPRequestImpl::Type() const
{
    return ESIPMessageType::Request;
}

void CSIPRequestImpl::Assign(const ISIPRequest& Copy)
{
    Method(Copy.Method());
    URI().Assign(Copy.URI());

    TSIPMessageImpl::Assign(Copy);
}

ESipMethod CSIPRequestImpl::Method() const
{
    return m_eMethod;
}

void CSIPRequestImpl::Method(ESipMethod eMethod)
{
    m_eMethod = eMethod;
}

const ISipURI& CSIPRequestImpl::URI() const
{
    return m_cURI;
}

ISipURI& CSIPRequestImpl::URI()
{
    return m_cURI;
}

bool CSIPRequestImpl::Parse(const char* pData, size_t uSize)
{
    return EParserResult::Success == CSipParser::ParseRequest(pData, uSize, *this);
}

void CSIPRequestImpl::Serialize(IOutputBuffer& Buffer) const
{
    CSipSerializer::SerializeRequest(*this, Buffer);
}