#ifndef _IEVTHANDLERDTMF_H_
#define _IEVTHANDLERDTMF_H_

#include <proxSIP/IRtpPhoneEvent.h>

//! Interface for processing DTMF events
class IEvtHandlerDTMF
{
public:
    virtual ~IEvtHandlerDTMF() = default;

    //! Callback when a DTMF event is received
    virtual void OnEvent(const IRtpPhoneEvent&) = 0;
};

#endif