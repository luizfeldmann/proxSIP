#include "CKeyValuePair.h"
#include <string>

/* CKeyValuePairImpl */

class CKeyValuePairImpl
{
public:
    std::string m_sKey;
    std::string m_sValue;

    //! Copy-construct
    CKeyValuePairImpl(const CKeyValuePairImpl&) = default;

    //! Copy-assign
    CKeyValuePairImpl& operator=(const CKeyValuePairImpl&) = default;

    //! Constructs blank
    CKeyValuePairImpl()
    {

    }

    //! Constructs with initial values
    CKeyValuePairImpl(const char* sName, const char* sValue)
        : m_sKey(sName)
        , m_sValue(sValue)
    {
    }

    //! Copies from another abstract pair
    CKeyValuePairImpl(const IKeyValuePair& other)
        : CKeyValuePairImpl(other.Key(), other.Value())
    {

    }
};

IMPLEMENT_PIMPL(CKeyValuePairImpl);

/* CKeyValuePair */

CKeyValuePair::CKeyValuePair()
    : TImplPtr(new CKeyValuePairImpl)
{

}

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
    return m_pImpl->m_sKey.c_str();
}

void CKeyValuePair::Key(const char* sName)
{
    m_pImpl->m_sKey = sName;
}

const char* CKeyValuePair::Value() const
{
    return m_pImpl->m_sValue.c_str();
}

void CKeyValuePair::Value(const char* sValue)
{
    m_pImpl->m_sValue = sValue;
}