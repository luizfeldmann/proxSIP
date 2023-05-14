#include "Internal/CSipRegistryImpl.h"
#include "ESipParameter.h"
#include <boost/log/trivial.hpp>

CSipRegistryImpl::CSipRegistryImpl()
{

}

/* Overrides from ISipRegistry */

void CSipRegistryImpl::Register(const char* sUser, const char* sLocation, unsigned int uExpires)
{
    // Find or insert the item
    auto& stData = m_mReg.insert({ sUser, SRegistryData() }).first->second;

    // Update record
    stData.m_expires = std::chrono::system_clock::now() + std::chrono::seconds(uExpires);
    stData.m_sLocation = sLocation;

    // Log
    BOOST_LOG_TRIVIAL(info) << "Registed: " << sUser << " at " << stData.m_sLocation << " expires in " << uExpires;
}

const char* CSipRegistryImpl::Locate(const char* sUser) const
{
    const char* sLocation = nullptr;
    auto itFind = m_mReg.find(sUser);

    if (itFind != m_mReg.cend())
    {
        const auto& stData = itFind->second;

        if (stData.m_expires > std::chrono::system_clock::now())
        {
            sLocation = stData.m_sLocation.c_str();
        }
    }

    return sLocation;
}