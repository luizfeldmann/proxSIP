#ifndef _TSIPMESSAGEIMPL_H_
#define _TSIPMESSAGEIMPL_H_

#include "CEndpointImpl.h"
#include "TBuffer.h"
#include <vector>

//! Internal implementation of #ISIPMessage
template<class Base>
class TSIPMessageImpl : public Base
{
protected:
    //! The source endpoint of the message
    CEndpointImpl m_edpSrc;

    //! The destination endpoint of the message
    CEndpointImpl m_edpDst;

    //! The buffer of message data
    TBuffer<std::vector<char>> m_buffer;

public:
    //! @name Overrides from #ISIPMessage
    //! @{
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