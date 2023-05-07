#ifndef _IUDPSERVER_H_
#define _IUDPSERVER_H_

#include "IUdpMessageHandler.h"
#include "IEndpoint.h"

//! Handles HTTP messages via UDP
class PROXSIP_API IUdpServer
{
public:
    virtual ~IUdpServer() = default;;

    //! Mutator to the locally bound endpoint
    virtual IEndpoint& LocalEndpoint() = 0;

    //! Accessor to the locally bound endpoint
    virtual const IEndpoint& LocalEndpoint() const = 0;

    //! Sets the object to receive the messages
    virtual void SetHandler(IUdpMessageHandler*) = 0;

    //! Starts the server
    virtual bool Start() = 0;

    //! Stops the server
    virtual bool Stop() = 0;

    //! Processes the server messages
    virtual void Poll() = 0;
};

#endif