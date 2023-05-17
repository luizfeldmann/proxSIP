#ifndef _ISIPURI_H_
#define _ISIPURI_H_

#include "ESipURIComponents.h"
#include "ISipField.h"

//! Represents a URI scheme in format sip:user:password@host:port;uri-parameters?headers
class PROXSIP_API ISipURI : public ISipField
{
public:
    virtual ~ISipURI() = default;

    //! Copies from another object
    virtual void Assign(const ISipURI&) = 0;

    //! Returns a bitwise enumeration of the components present in the URI
    virtual ESipURIComponents QueryComponents() const = 0;

    //! Deletes the requested components
    virtual void DropComponents(ESipURIComponents) = 0;

    //! Keeps only the requested components
    virtual void KeepComponents(ESipURIComponents) = 0;

    //! Read the protocol
    virtual const char* Protocol() const = 0;

    //! Sets the protocol
    virtual void Protocol(const char*) = 0;

    //! Reads the user name
    virtual const char* User() const = 0;

    //! Sets the user name
    virtual void User(const char*) = 0;

    //! Reads the password
    virtual const char* Password() const = 0;

    //! Sets the password
    virtual void Password(const char*) = 0;

    //! Reads the host name
    virtual const char* Host() const = 0;

    //! Sets the host name
    virtual void Host(const char*) = 0;

    //! Reads the port number
    virtual unsigned short Port() const = 0;

    //! Sets the port number
    virtual void Port(unsigned short) = 0;

    //! Returns a C-string from the URI
    virtual const char* c_str() const = 0;
};

#endif