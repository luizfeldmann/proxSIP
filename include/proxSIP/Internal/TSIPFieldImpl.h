#ifndef _TSIPFIELDIMPL_H_
#define _TSIPFIELDIMPL_H_

#include "ISipField.h"
#include "CKeyValueCollectionImpl.h"

namespace detail
{
    //! Parses the parameters of a SIP header field
    bool SipFieldParseParams(const char*, size_t, IKeyValueCollection&);

    //! Serializes the parameters of a SIP header field
    void SipFieldSerializeParams(const IKeyValueCollection&, IBuffer&);
};

//! Internal implementation of #ISIPFields
template<class Base>
class TSIPFieldImpl : public Base
{
private:
    CKeyValueCollectionImpl m_params;

public:

    //! @name Overrides from #ISIPFields
    //! @{
    const IKeyValueCollection& Parameters() const
    {
        return m_params;
    }

    IKeyValueCollection& Parameters()
    {
        return m_params;
    }

    bool Parse(const char* pData, size_t uSize)
    {
        return detail::SipFieldParseParams(pData, uSize, m_params);
    }

    void Serialize(IBuffer& Buffer) const
    {
        detail::SipFieldSerializeParams(m_params, Buffer);
    }
    //! @}
};

#endif