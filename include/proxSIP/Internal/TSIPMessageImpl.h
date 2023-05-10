#ifndef _TSIPMESSAGEIMPL_H_
#define _TSIPMESSAGEIMPL_H_

#include "CEndpointImpl.h"
#include "CKeyValueCollectionImpl.h"
#include "TBuffer.h"
#include <vector>
#include <string>

//! Internal implementation of #ISIPMessage
template<class Base>
class TSIPMessageImpl : public Base
{
protected:
    //! The version of the protocol
    std::string m_sVersion;

    //! The source endpoint of the message
    CEndpointImpl m_edpSrc;

    //! The destination endpoint of the message
    CEndpointImpl m_edpDst;

    //! Collection of fields
    CKeyValueCollectionImpl m_fields;

    //! The buffer of message data
    TBuffer<std::vector<char>> m_buffer;

public:
    //! @name Overrides from #ISIPMessage
    //! @{
    const char* Version() const
    {
        return m_sVersion.c_str();
    }

    void Version(const char* szVersion)
    {
        m_sVersion = szVersion;
    }

    const IEndpoint& Source() const override
    {
        return m_edpSrc;
    }

    IEndpoint& Source() override
    {
        return m_edpSrc;
    }

    const IEndpoint& Destination() const override
    {
        return m_edpDst;
    }

    IEndpoint& Destination() override
    {
        return m_edpDst;
    }

    const IKeyValueCollection& Fields() const override
    {
        return m_fields;
    }

    IKeyValueCollection& Fields() override
    {
        return m_fields;
    }

    const IBuffer& Content() const override
    {
        return m_buffer;
    }

    IBuffer& Content() override
    {
        return m_buffer;
    }
    //! @}
};


#endif