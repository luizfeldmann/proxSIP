#ifndef _ISIPRESPONSE_H_
#define _ISIPRESPONSE_H_

#include "ISIPMessage.h"
#include "ESipStatusCode.h"

//! Representation of the data on a SIP response
class PROXSIP_API ISIPResponse : public ISIPMessage
{
public:
    virtual ~ISIPResponse() = default;

    //! Copies from another response
    virtual void Assign(const ISIPResponse&) = 0;

    //! Reads the status code of the response
    virtual ESipStatusCode Status() const = 0;

    //! Sets the status code of the response
    virtual void Status(ESipStatusCode) = 0;
};

#endif