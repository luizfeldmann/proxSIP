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

    //! Unique ID of the session
    std::string m_sCallID;

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
    
    //! Copies the message data from another object 
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
        CallID(Copy.CallID());

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

    //! @copydoc ISIPMessage::Version
    const char* Version() const
    {
        return m_sVersion.c_str();
    }

    //! @copydoc ISIPMessage::Version
    void Version(const char* szVersion)
    {
        m_sVersion = szVersion;
    }

    //! @copydoc ISIPMessage::Source
    const IEndpoint& Source() const override
    {
        return m_edpSrc;
    }

    //! @copydoc ISIPMessage::Source
    IEndpoint& Source() override
    {
        return m_edpSrc;
    }

    //! @copydoc ISIPMessage::Destination
    const IEndpoint& Destination() const override
    {
        return m_edpDst;
    }

    //! @copydoc ISIPMessage::Destination
    IEndpoint& Destination() override
    {
        return m_edpDst;
    }

    //! @copydoc ISIPMessage::Via
    const IContainer<ISipVia>& Via() const override
    {
        return m_vias;
    }

    //! @copydoc ISIPMessage::Via
    IContainer<ISipVia>& Via()
    {
        return m_vias;
    }

    //! @copydoc ISIPMessage::From
    const ISipContact& From() const override
    {
        return m_from;
    }

    //! @copydoc ISIPMessage::From
    ISipContact& From() override
    {
        return m_from;
    }

    //! @copydoc ISIPMessage::To
    const ISipContact& To() const override
    {
        return m_to;
    }

    //! @copydoc ISIPMessage::To
    ISipContact& To() override
    {
        return m_to;
    }

    //! @copydoc ISIPMessage::CallID
    const char* CallID() const
    {
        return m_sCallID.c_str();
    }

    //! @copydoc ISIPMessage::CallID
    void CallID(const char* sCallID)
    {
        m_sCallID.assign(sCallID);
    }

    //! @copydoc ISIPMessage::Contact
    const IContainer<ISipContact>& Contact() const
    {
        return m_contacts;
    }

    //! @copydoc ISIPMessage::Contact
    IContainer<ISipContact>& Contact()
    {
        return m_contacts;
    }

    //! @copydoc ISIPMessage::Fields
    const IKeyValueCollection& Fields() const override
    {
        return m_fields;
    }

    //! @copydoc ISIPMessage::Fields
    IKeyValueCollection& Fields() override
    {
        return m_fields;
    }

    //! @copydoc ISIPMessage::ContentType
    const char* ContentType() const override
    {
        return m_sContentType.c_str();
    }

    //! @copydoc ISIPMessage::ContentType
    void ContentType(const char* sContentType) override
    {
        m_sContentType.assign(sContentType);
    }

    //! @copydoc ISIPMessage::ContentLength
    size_t ContentLength() const override
    {
        return m_uContentLength;
    }

    //! @copydoc ISIPMessage::ContentLength
    void ContentLength(size_t uLen) override
    {
        m_uContentLength = uLen;
    }

    //! @copydoc ISIPMessage::Content
    const IBuffer& Content() const override
    {
        return m_buffer;
    }

    //! @copydoc ISIPMessage::Content
    IBuffer& Content() override
    {
        return m_buffer;
    }
    //! @}
};


#endif