#ifndef _CSDPMESSAGEIMPL_H_
#define _CSDPMESSAGEIMPL_H_

#include "ISdpMessage.h"
#include "CSdpOriginatorImpl.h"
#include "CSdpConnectionImpl.h"
#include "CSdpTimeImpl.h"
#include "CSdpMediaImpl.h"
#include "TContainer.h"
#include <boost/optional.hpp>
#include <string>

//! @copybrief ISdpMessage
class CSdpMessageImpl : public ISdpMessage
{
private:
    unsigned char m_uVersion;
    CSdpOriginatorImpl m_originator;
    std::string m_sSessionName;
    //boost::optional<std::string> m_sSessionInfo;
    //boost::optional<std::string> m_sSessionURI;
    //boost::optional<std::string> m_sEmail;
    //boost::optional<std::string> m_sPhone;
    CSdpConnectionImpl m_connection;
    //boost::optional<CSdpBandwidth> m_sBandwidth;
    //boost::optional<CSdpTimezone> m_sZone;
    //boost::optional<CSdpCryptoKey> m_sKey;
    //TContainer<ISdpAttribute, CSdpAttributeImpl> m_attribs;
    CSdpTimeImpl m_sTime;
    //boost::optional<CSdpRepeatTimeImpl> m_sRepeat;
    TContainer<ISdpMedia, CSdpMediaImpl> m_medias;

public:
    CSdpMessageImpl();

    //! @name Overrides from ISdpMessage
    //! @{
    //! @}

    //! @name Overrides from IMessage
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}
};

#endif