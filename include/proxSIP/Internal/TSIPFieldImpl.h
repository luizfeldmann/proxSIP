#ifndef _TSIPFIELDIMPL_H_
#define _TSIPFIELDIMPL_H_

#include "ISipField.h"
#include "CKeyValueCollectionImpl.h"

namespace detail
{
    //! Parses the parameters of a SIP header field
    bool SipFieldParseParams(const char*, size_t, IKeyValueCollection&);

    //! Serializes the parameters of a SIP header field
    void SipFieldSerializeParams(const IKeyValueCollection&, IOutputBuffer&);
};

//! Internal implementation of ISipField
template<class Base>
class TSIPFieldImpl : public Base
{
private:
    CKeyValueCollectionImpl m_params;

public:

    //! @name Overrides from #ISIPFields
    //! @{
    
    //! Copies the data of another object
    void Assign(const ISipField& Copy) override
    {
        Parameters().Assign(Copy.Parameters());
    }

    //! @copydoc ISipField::Parameters
    const IKeyValueCollection& Parameters() const
    {
        return m_params;
    }

    //! @copydoc ISipField::Parameters
    IKeyValueCollection& Parameters()
    {
        return m_params;
    }

    //! @copydoc ISipField::Parse
    bool Parse(const char* pData, size_t uSize)
    {
        return detail::SipFieldParseParams(pData, uSize, m_params);
    }

    //! @copydoc ISipField::Serialize
    void Serialize(IOutputBuffer& Buffer) const
    {
        detail::SipFieldSerializeParams(m_params, Buffer);
    }
    //! @}
};

#endif