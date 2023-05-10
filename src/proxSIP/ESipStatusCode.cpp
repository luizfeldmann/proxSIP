#include "ESipStatusCode.h"
#include <map>
#include <string>

/* Enum to Name */

using code_status_map_t = std::map<ESipStatusCode, std::string>;

static const code_status_map_t& GetMapCodeToStatus()
{
    static const code_status_map_t theMap
    {
        /* Provisional */
        { ESipStatusCode::Trying, "Trying"},
        { ESipStatusCode::Ringing, "Ringing"},
        { ESipStatusCode::Forwarded, "Call Is Being Forwarded"},
        { ESipStatusCode::Queued, "Queued"},
        { ESipStatusCode::SessionProgress, "Session Progress"},
        /* Successful */
        { ESipStatusCode::Ok, "OK"},
        /* Redirection */
        { ESipStatusCode::MultipleChoices, "Multiple Choices"},
        { ESipStatusCode::MovedPermanently, "Moved Permanently"},
        { ESipStatusCode::MovedTemporarily, "Moved Temporarily"},
        { ESipStatusCode::UseProxy, "Use Proxy"},
        { ESipStatusCode::AlternativeService, "Alternative Service"},
        /* Request Failure */
        { ESipStatusCode::BadRequest, "Bad Request"},
        { ESipStatusCode::Unauthorized, "Unauthorized"},
        { ESipStatusCode::PaymentRequired, "Payment Required"},
        { ESipStatusCode::Forbidden, "Forbidden"},
        { ESipStatusCode::NotFound, "Not Found"},
        { ESipStatusCode::MethodNotAllowed, "Method Not Allowed"},
        { ESipStatusCode::NotAcceptable, "Not Acceptable"},
        { ESipStatusCode::ProxyAuthenticationRequired, "Proxy Authentication Required"},
        { ESipStatusCode::RequestTimeout, "Request Timeout"},
        { ESipStatusCode::Gone, "Gone"},
        { ESipStatusCode::RequestEntityTooLarge, "Request Entity Too Large"},
        { ESipStatusCode::RequestTooLong, "Request-URI Too Long"},
        { ESipStatusCode::UnsupportedMediaType, "Unsupported Media Type"},
        { ESipStatusCode::UnsupportedScheme, "Unsupported URI Scheme"},
        { ESipStatusCode::BadExtension, "Bad Extension"},
        { ESipStatusCode::ExtensionRequired, "Extension Required"},
        { ESipStatusCode::IntervalTooBrief, "Interval Too Brief"},
        { ESipStatusCode::TemporarilyUnavailable, "Temporarily Unavailable"},
        { ESipStatusCode::CallTransactionDoesNotExist, "Call/Transaction Does Not Exist"},
        { ESipStatusCode::LoopDetected, "Loop Detected"},
        { ESipStatusCode::TooManyHops, "Too Many Hops"},
        { ESipStatusCode::AddressIncomplete, "Address Incomplete"},
        { ESipStatusCode::Ambiguous, "Ambiguous"},
        { ESipStatusCode::BusyHere, "Busy Here"},
        { ESipStatusCode::RequestTerminated, "Request Terminated"},
        { ESipStatusCode::NotAcceptableHere, "Not Acceptable Here"},
        { ESipStatusCode::RequestPending, "Request Pending"},
        { ESipStatusCode::Undecipherable, "Undecipherable"},
        /* Server Failure */
        { ESipStatusCode::ServerInternalError, "Server Internal Error"},
        { ESipStatusCode::NotImplemented, "Not Implemented"},
        { ESipStatusCode::BadGateway, "Bad Gateway"},
        { ESipStatusCode::ServiceUnavailable, "Service Unavailable"},
        { ESipStatusCode::ServerTimeout, "Server Time-out"},
        { ESipStatusCode::VersionNotSupported, "Version Not Supported"},
        { ESipStatusCode::MessageTooLarge, "Message Too Large"},
        /* Global Failures */
        { ESipStatusCode::BusyEverywhere, "Busy Everywhere"},
        { ESipStatusCode::Decline, "Decline"},
        { ESipStatusCode::DoesNotExistAnywhere, "Does Not Exist Anywhere"},
        { ESipStatusCode::NotAcceptableGlobal, "Not Acceptable"},
    };

    return theMap;
}

const char* GetSipStatusCodeStr(ESipStatusCode eCode)
{
    const char* szStatus = nullptr;

    const auto& rMap = GetMapCodeToStatus();
    auto itFind = rMap.find(eCode);

    if (rMap.cend() != itFind)
        szStatus = itFind->second.c_str();

    return szStatus;
}