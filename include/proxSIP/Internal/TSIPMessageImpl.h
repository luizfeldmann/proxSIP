#ifndef _TSIPMESSAGEIMPL_H_
#define _TSIPMESSAGEIMPL_H_

#include "ISIPMessage.h"
#include "CEndpointImpl.h"
#include "CKeyValueCollectionImpl.h"
#include "CSipContactImpl.h"
#include "CSipViaImpl.h"
#include "TBuffer.h"
#include "TContainer.h"
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

    //! The "Via" fields
    TContainer<ISipVia, CSipViaImpl> m_vias;

    //! The "To" field
    CSipContactImpl m_to;

    //! The "From" field
    CSipContactImpl m_from;

    //! The "Contact" fields
    TContainer<ISipContact, CSipContactImpl> m_contacts;

    //! Collection of fields
    CKeyValueCollectionImpl m_fields;

    //! Content type of the body
    std::string m_sContentType;

    //! Size of the body
    size_t m_uContentLength;

    //! The buffer of message data
    TBuffer<std::vector<char>> m_buffer;

public:
    TSIPMessageImpl()
        : m_uContentLength(0)
    {

    }

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
        CopyContainer(Copy.Via(), Via(), TMemberAssigner<ISipVia>(&ISipVia::Assign));
        From().Assign(Copy.From());
        To().Assign(Copy.To());
        CopyContainer(Copy.Contact(), Contact(), TMemberAssigner<ISipContact>(&ISipContact::Assign));

        // Copy other fields
        Fields().Assign(Copy.Fields());

        // Copy body content
        ContentType(Copy.ContentType());
        ContentLength(Copy.ContentLength());

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

    const IContainer<ISipVia>& Via() const override
    {
        return m_vias;
    }

    IContainer<ISipVia>& Via()
    {
        return m_vias;
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

    const IContainer<ISipContact>& Contact() const
    {
        return m_contacts;
    }

    IContainer<ISipContact>& Contact()
    {
        return m_contacts;
    }

    const IKeyValueCollection& Fields() const override
    {
        return m_fields;
    }

    IKeyValueCollection& Fields() override
    {
        return m_fields;
    }

    const char* ContentType() const override
    {
        return m_sContentType.c_str();
    }

    void ContentType(const char* sContentType) override
    {
        m_sContentType.assign(sContentType);
    }

    size_t ContentLength() const override
    {
        return m_uContentLength;
    }

    void ContentLength(size_t uLen) override
    {
        m_uContentLength = uLen;
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