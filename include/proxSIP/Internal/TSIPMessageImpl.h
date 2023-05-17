#ifndef _TSIPMESSAGEIMPL_H_
#define _TSIPMESSAGEIMPL_H_

#include "ISIPMessage.h"
#include "CEndpointImpl.h"
#include "CKeyValueCollectionImpl.h"
#include "CSipContactImpl.h"
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

    //! The "To" field
    CSipContactImpl m_to;

    //! The "From" field
    CSipContactImpl m_from;

    //! Collection of fields
    CKeyValueCollectionImpl m_fields;

    //! The buffer of message data
    TBuffer<std::vector<char>> m_buffer;

public:
    //! @name Overrides from #ISIPMessage
    //! @{
    void Assign(const ISIPMessage& Copy) override
    {
        // Copy endpoints
        Source().Assign(Copy.Source());
        Destination().Assign(Copy.Destination());

        // Copy version
        Version(Copy.Version());

        // Copy own storage fields
        From().Assign(Copy.From());
        To().Assign(Copy.To());

        // Copy other fields
        Fields().Assign(Copy.Fields());

        // Copy body content
        const auto& copyBody = Copy.Content();

        if (copyBody.size())
        {
            Content().write(copyBody.cbegin(), copyBody.size());
        }
    }

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

    const ISipContact& From() const override
    {
        return m_from;
    }

    ISipContact& From() override
    {
        return m_from;
    }

    const ISipContact& To() const override
    {
        return m_to;
    }

    ISipContact& To() override
    {
        return m_to;
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