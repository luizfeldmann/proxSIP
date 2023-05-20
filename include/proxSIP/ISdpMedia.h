#ifndef _ISDPMEDIA_H_
#define _ISDPMEDIA_H_

#include "ISdpField.h"
#include "IContainer.h"
#include "ESdpMediaType.h"
#include "ESdpMediaProto.h"
#include "ISdpAttribute.h"

//! Describes a media stream in the session
class PROXSIP_API ISdpMedia : public ISdpField
{
public:
    virtual ~ISdpMedia() = default;

    //! Reads the media type
    virtual ESdpMediaType MediaType() const = 0;

    //! Sets the media type
    virtual void MediaType(ESdpMediaType) = 0;

    //! Reads the media protocol
    virtual ESdpMediaProto MediaProtocol() const = 0;

    //! Sets the media protocol
    virtual void MediaProtocol(ESdpMediaProto) = 0;

    //! Reads the media port
    virtual unsigned short Port() const = 0;

    //! Sets the media port
    virtual void Port(unsigned short) = 0;

    //! Reads the number of ports (pairs) used
    virtual unsigned char NumPorts() const = 0;

    //! Sets the number of ports
    virtual void NumPorts(unsigned char) = 0;

    //! Reads the format descriptors
    virtual const char* Formats() const = 0;

    //! Sets the format descriptors
    virtual void Formats(const char*) = 0;

    //! Accessor to the collection of attributes
    virtual const IContainer<ISdpAttribute>& Attributes() const = 0;

    //! Mutator to the collection of attributes
    virtual IContainer<ISdpAttribute>& Attributes() = 0;
};

#endif