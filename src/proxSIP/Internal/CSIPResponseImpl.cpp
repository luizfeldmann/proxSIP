#include "Internal/CSIPResponseImpl.h"
#include "CSipParser.h"
#include "CSipSerializer.h"

/* CSIPResponseImpl */

CSIPResponseImpl::CSIPResponseImpl()
    : m_eStatus(ESipStatusCode::Unknown)
{

}

CSIPResponseImpl::CSIPResponseImpl(const CSIPResponseImpl&) = default;

CSIPResponseImpl& CSIPResponseImpl::operator=(const CSIPResponseImpl&) = default;

CSIPResponseImpl::CSIPResponseImpl(CSIPResponseImpl&&) noexcept = default;

CSIPResponseImpl& CSIPResponseImpl::operator=(CSIPResponseImpl&&) noexcept = default;

/* ISIPMessage */

const ESIPMessageType CSIPResponseImpl::Type() const
{
    return ESIPMessageType::Response;
}

/* ISIPRequest */

void CSIPResponseImpl::Assign(const ISIPResponse& Copy)
{
    Status(Copy.Status());
    TSIPMessageImpl::Assign(Copy);
}

ESipStatusCode CSIPResponseImpl::Status() const
{
    return m_eStatus;
}

void CSIPResponseImpl::Status(ESipStatusCode eStatus)
{
    m_eStatus = eStatus;
}

bool CSIPResponseImpl::Parse(const char* pData, size_t uSize)
{
    return EParserResult::Success == CSipParser::ParseResponse(pData, uSize, *this);
}

void CSIPResponseImpl::Serialize(IOutputBuffer& Buffer) const
{
    CSipSerializer::SerializeResponse(*this, Buffer);
}