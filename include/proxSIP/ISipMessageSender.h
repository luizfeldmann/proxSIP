#ifndef _ISIPMESSAGESENDER_
#define _ISIPMESSAGESENDER_

#include "ISIPMessage.h"

//! Interface for sending out SIP messages
class PROXSIP_API ISipMessageSender
{
public:
    virtual ~ISipMessageSender() = default;

    //! Sends out a SIP message
    virtual void SendMessage(const ISIPMessage&) = 0;
};

#endif