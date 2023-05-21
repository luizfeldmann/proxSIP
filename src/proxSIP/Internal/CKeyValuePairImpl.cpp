#include "Internal/CKeyValuePairImpl.h"

CKeyValuePairImpl::CKeyValuePairImpl(const char* sKey, const char* sValue)
    : m_sKey(sKey)
    , m_sValue(sValue)
{

}

CKeyValuePairImpl::CKeyValuePairImpl(const IKeyValuePair& copy)
    : CKeyValuePairImpl(copy.Key(), copy.Value())
{

}

CKeyValuePairImpl::CKeyValuePairImpl(const CKeyValuePairImpl&) = default;

CKeyValuePairImpl& CKeyValuePairImpl::operator=(const CKeyValuePairImpl&) = default;

CKeyValuePairImpl::CKeyValuePairImpl(CKeyValuePairImpl&&) noexcept = default;

CKeyValuePairImpl& CKeyValuePairImpl::operator=(CKeyValuePairImpl&&) noexcept = default;

const char* CKeyValuePairImpl::Key() const
{
    return m_sKey.c_str();
}

void CKeyValuePairImpl::Key(const char* sKey)
{
    m_sKey.assign(sKey);
}

const char* CKeyValuePairImpl::Value() const
{
    return m_sValue.c_str();
}

void CKeyValuePairImpl::Value(const char* szValue)
{
    m_sValue = szValue;
}