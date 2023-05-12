#include "CAppConfig.h"
#include "proxSIP/CEndpoint.h"
#include <boost/log/trivial.hpp>
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/json.hpp>
#include <boost/exception_ptr.hpp>

/* Util */

static boost::filesystem::path GetDefaultConfigFilePath()
{
    auto path = boost::dll::program_location();
    path.replace_extension("json");

    return path;
}

/* CAppConfigImpl */

class CAppConfigImpl
{
public:
    CAppConfigImpl()
    {

    }

    //! Server configuration
    struct SServerConfig : CEndpoint
    {
        // Read server configuration
        void Read(const boost::json::object& jObj)
        {
            Address(jObj.at("IP").as_string().c_str());
            Port(jObj.at("Port").to_number<unsigned short>());
        }
    } m_stServer; //!< @copydoc SServerConfig

    //! User data
    struct SUserData : public IUserAccountCollection
    {
        std::map<std::string, std::string> m_mUserPass;

        //! Reads user data
        void Read(const boost::json::object& jObj)
        {
            // Iterate each user record
            for (const auto& rUser : jObj)
            {
                const char* sUsername = rUser.key_c_str();
                const char* sPassword = rUser.value().as_string().c_str();

                // Add to list
                auto insert = m_mUserPass.insert({ sUsername , sPassword });

                // Check if add successful
                if (!insert.second)
                {
                    BOOST_LOG_TRIVIAL(warning) << "Repeated user record: " << sUsername;
                }
            }
        }

        //! @name Overrides from IUserAccountCollection
        //! @{
        const char* GetUserPassword(const char*, const char* sUsername) const
        {
            const char* sPassword = nullptr;

            auto itFind = m_mUserPass.find(sUsername);
            if (m_mUserPass.cend() != itFind)
                sPassword = itFind->second.c_str();

            return sPassword;
        }
        //! @}
    } m_stUsers; //!< @copydoc SUserData


    //! Parses the root level of the application configuration file
    void Read(const boost::json::object& jAppConfig)
    {
        m_stServer.Read(jAppConfig.at("Server").as_object());
        m_stUsers.Read(jAppConfig.at("Users").as_object());
    }

    //! Gets the accessor to the user accounts
    const IUserAccountCollection& GetUsers() const
    {
        return m_stUsers;
    }
};

/* CAppConfig */

CAppConfig::~CAppConfig()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

CAppConfig::CAppConfig()
    : CAppConfig(nullptr)
{

}

CAppConfig::CAppConfig(const char* szFile)
    : m_pImpl(new CAppConfigImpl)
{
    boost::filesystem::path configPath;

    if (!szFile)
    {
        // If no file is requested, use default
        configPath = GetDefaultConfigFilePath();
    }
    else
    {
        // Try using the supplied file
        configPath = szFile;

        if (!boost::filesystem::exists(configPath))
        {
            // Fallback to the default in case the required file is missing
            BOOST_LOG_TRIVIAL(error) << "Requested file does not exist: " << configPath;
            configPath = GetDefaultConfigFilePath();
        }
    }

    // Check the file exists; it's possible the default file is also missing ...
    if (!boost::filesystem::exists(configPath))
    {
        BOOST_LOG_TRIVIAL(error) << "Configuration file does not exist: " << configPath;
    }
    else
    {
        // Open the file for reading
        boost::filesystem::ifstream ifConfig;
        ifConfig.open(configPath);

        // Parse into JSON struct
        boost::json::error_code error;
        boost::json::value jAppConfig = boost::json::parse(ifConfig, error);

        if (error)
        {
            BOOST_LOG_TRIVIAL(error) << "Failed to parse configuration file: " << error.message();
        }
        else if (!jAppConfig.is_object())
        {
            BOOST_LOG_TRIVIAL(error) << "Configuration file does not contain root object";
        }
        else
        {
            // Try parsing the data
            // Missing or incorrect fields will throw exceptions
            try
            {
                m_pImpl->Read(jAppConfig.as_object());
            }
            catch (boost::exception const& ex)
            {
                BOOST_LOG_TRIVIAL(error) << "Failed parsing configuration: " << boost::diagnostic_information_what(ex);
            }
        }
    }
}

const IEndpoint& CAppConfig::ServerLocalEndpoint() const
{
    return m_pImpl->m_stServer;
}

const IUserAccountCollection& CAppConfig::GetUsers() const
{
    return m_pImpl->GetUsers();
}