#include "Internal/CSipRegistryImpl.h"
#include "ESipParameter.h"
#include <boost/log/trivial.hpp>

CSipRegistryImpl::CSipRegistryImpl()
{

}

/* Overrides from ISipRegistry */

void CSipRegistryImpl::Register(const char*, const ISipContact& Contact, const ISipVia& Via)
{
    std::string sContactURI = Contact.URI();;

    // Find or insert the item
    auto& stData = m_mReg.insert({ sContactURI, SRegistryData() }).first->second;

    // Reads expiration time
    unsigned int uExpSecs = 3600;
    {
        const char* sExpire = Contact.Parameters().Find(SipGetParamStr(ESipParameter::expires));
        if (sExpire)
        {
            if (!sscanf(sExpire, "%ul", &uExpSecs))
                BOOST_LOG_TRIVIAL(warning) << "Unable to parse expiration time:" << sExpire;
        }
        else
        {
            BOOST_LOG_TRIVIAL(warning) << "Expiration time not provided, assuming " << uExpSecs;
        }

        // Save updated expiration time
        stData.m_expires = std::chrono::system_clock::now() + std::chrono::seconds();
    }

    // Save updated VIA
    stData.m_sViaURI = Via.URI();

    // Log
    BOOST_LOG_TRIVIAL(info) << "Registed: " << sContactURI << " at " << stData.m_sViaURI << " expires in " << uExpSecs;
}

bool CSipRegistryImpl::Locate(const char*, const ISipContact& Contact, ISipVia& Via) const
{
    bool bStatus = false;
    auto itFind = m_mReg.find(Contact.URI());

    if (itFind != m_mReg.cend())
    {
        const auto& stData = itFind->second;

        if (stData.m_expires < std::chrono::system_clock::now())
        {
            Via.URI(stData.m_sViaURI.c_str());
            bStatus = true;
        }
    }

    return bStatus;
}