#ifndef _CAPPCONFIG_H_
#define _CAPPCONFIG_H_

#include <proxSIP/IEndpoint.h>
#include <proxSIP/IUserAccountCollection.h>
#include <string>

class CAppConfigImpl;

//! Reads app configuration
class CAppConfig
{
private:
    CAppConfigImpl* m_pImpl;

public:
    ~CAppConfig();

    //! Reads configuration from the default location
    CAppConfig();

    //! Reads configurations from the provided file path
    CAppConfig(const char* szFile);

    //! Reads the local endpoint of the server
    const IEndpoint& ServerLocalEndpoint() const;

    //! Retrieves the collection of user accounts
    const IUserAccountCollection* GetUsers() const;

    //! Reads the credentials to command the remote switch
    void GetSwitchCredentials(std::string& sUser, std::string& sPass);

    //! Reads the remote endpoint of the remote switch
    void GetSwitchEndpoint(std::string& sHost, unsigned short& uPort, std::string& sTarget);

    //! Reads the time between activations of the switch
    unsigned short GetSwitchInterval();
};

#endif