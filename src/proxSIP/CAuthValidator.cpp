#include "CAuthValidator.h"
#include "Internal/CAuthValidatorImpl.h"

CAuthValidator::CAuthValidator()
    : m_pImpl(new CAuthValidatorImpl)
{

}

CAuthValidator::~CAuthValidator()
{
    delete m_pImpl;
    m_pImpl = nullptr;
}

void CAuthValidator::SetAccounts(const IUserAccountCollection* pAccounts)
{
    m_pImpl->SetAccounts(pAccounts);
}

ESipStatusCode CAuthValidator::ValidateAuth(IAuthDigest& Digest)
{
    return m_pImpl->ValidateAuth(Digest);
}