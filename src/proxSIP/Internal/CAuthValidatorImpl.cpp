#include "Internal/CAuthValidatorImpl.h"

IAuthValidator::~IAuthValidator() = default;

CAuthValidatorImpl::CAuthValidatorImpl()
    : m_pAccounts(nullptr)
{

}

void CAuthValidatorImpl::SetAccounts(const IUserAccountCollection* pAccounts)
{
    m_pAccounts = pAccounts;
}

ESipStatusCode CAuthValidatorImpl::ValidateAuth(IAuthDigest& Digest)
{
    // TODO: Implement authentication
    return ESipStatusCode::Ok;
}