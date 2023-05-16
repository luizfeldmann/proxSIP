#ifndef _CSIPURIIMPL_H_
#define _CSIPURIIMPL_H_

#include "ISipURI.h"
#include "TSIPFieldImpl.h"
#include <boost/optional.hpp>

//! Implementation of #ISipURI
//! @details @copybrief ISipURI
class CSipURIImpl : public TSIPFieldImpl<ISipURI>
{
public:
    CSipURIImpl();

    //! Type used to optionally store a string
    using opt_string = boost::optional<std::string>;

    //! @name Overrides from #ISipURI
    //! @{
    ESipURIComponents QueryComponents() const override;

    void DropComponents(ESipURIComponents) override;

    void KeepComponents(ESipURIComponents) override;

    const char* Protocol() const override;

    void Protocol(const char*) override;

    const char* User() const override;

    void User(const char*) override;

    const char* Password() const override;

    void Password(const char*) override;

    const char* Host() const override;

    void Host(const char*) override;

    unsigned short Port() const override;

    void Port(unsigned short) override;
    //! @}
     
    //! @name Overrides from #ISipField
    //! @{
    bool Parse(const char*, size_t) override;

    void Serialize(IOutputBuffer&) const override;
    //! @}

private:
    //! Stores the protocol
    opt_string m_proto;

    //! Stores the user name
    opt_string m_user;

    //! Stores the user password
    opt_string m_password;

    //! Store the host name
    opt_string m_host;

    //! Stores the port number
    boost::optional<unsigned short> m_port;

    //! Parse the protocol name in the beginning of the URI
    bool ParseProtocol(const char*& pData, const char* const pEnd);

    //! Parses a range in format 'user(:pass)'
    bool ParseUserPass(const char* pFirst, const char* pSep, const char* pEnd);
    
    //! Parses a range in format 'hostname(:port)'
    bool ParseHostPort(const char* pFirst, const char* pSep, const char* pEnd);

    //! Parses a range in format 'first(:second)'
    bool ParseHeuristic(const char* pFirst, const char* pColon, const char* pEnd);

    //! Parses kernel of the URI (user, pass, host, port); no protocol and no parameters
    bool DoParse(const char* pData, const char* pColonBefore, const char* pAt, const char* pColonAfter, const char* pEnd);
};

#endif