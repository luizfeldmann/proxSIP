#include "CKeyValuePair.h"
#include "Internal/CKeyValuePairImpl.h"

/* CKeyValuePairImpl */

IMPLEMENT_PIMPL(CKeyValuePairImpl);

/* CKeyValuePair */

CKeyValuePair::CKeyValuePair(const char* sName, const char* sValue)
    : TImplPtr(new CKeyValuePairImpl(sName, sValue))
{

}

CKeyValuePair::CKeyValuePair(const IKeyValuePair& copy)
    : TImplPtr(new CKeyValuePairImpl(copy))
{

}

/* Overrides from IKeyValuePair */

const char* CKeyValuePair::Key() const
{
    return m_pImpl->Key();
}

void CKeyValuePair::Key(const char* sKey)
{
    m_pImpl->Key(sKey);
}

const char* CKeyValuePair::Value() const
{
    return m_pImpl->Value();
}

void CKeyValuePair::Value(const char* sValue)
{
    m_pImpl->Value(sValue);
}