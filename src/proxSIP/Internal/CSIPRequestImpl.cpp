#include "Internal/CSIPRequestImpl.h"

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

ESipMethod CSIPRequestImpl::Method() const
{
    return m_eMethod;
}

void CSIPRequestImpl::Method(ESipMethod eMethod)
{
    m_eMethod = eMethod;
}

const char* CSIPRequestImpl::URI() const
{
    return m_sURI.c_str();
}

void CSIPRequestImpl::URI(const char* sReqUri)
{
    m_sURI = sReqUri;
}

const char* CSIPRequestImpl::Version() const
{
    return m_sVersion.c_str();
}

void CSIPRequestImpl::Version(const char* sVersion)
{
    m_sVersion = sVersion;
}