#include "ESipURIComponents.h"

ESipURIComponents operator|(ESipURIComponents a, ESipURIComponents b)
{
    const auto _A = static_cast<unsigned int>(a);
    const auto _B = static_cast<unsigned int>(b);

    return static_cast<ESipURIComponents>(_A | _B);
}

ESipURIComponents operator&(ESipURIComponents a, ESipURIComponents b)
{
    const auto _A = static_cast<unsigned int>(a);
    const auto _B = static_cast<unsigned int>(b);

    return static_cast<ESipURIComponents>(_A & _B);
}

ESipURIComponents operator~(ESipURIComponents x)
{
    const auto _X = static_cast<unsigned int>(x);
    return static_cast<ESipURIComponents>(~_X);
}