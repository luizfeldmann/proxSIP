#ifndef _ESIPSTATUSCODE_H_
#define _ESIPSTATUSCODE_H_

#include "proxSIPExports.h"

//! Response status codes
enum class ESipStatusCode
{
    Unknown = 0,
    /* Provisional */
    Trying = 100,
    Ringing = 180,
    Forwarded = 181,
    Queued = 182,
    SessionProgress = 183,
    /* Successful */
    Ok = 200,
    /* Redirection */
    MultipleChoices = 300,
    MovedPermanently = 301,
    MovedTemporarily = 302,
    UseProxy = 305,
    AlternativeService = 380,
    /* Request Failure */
    BadRequest = 400,
    Unauthorized = 401,
    PaymentRequired = 402,
    Forbidden = 403,
    NotFound = 404,
    MethodNotAllowed = 405,
    NotAcceptable = 406,
    ProxyAuthenticationRequired = 407,
    RequestTimeout = 408,
    Gone = 410,
    RequestEntityTooLarge = 413,
    RequestTooLong = 414,
    UnsupportedMediaType = 415,
    UnsupportedScheme = 416,
    BadExtension = 420,
    ExtensionRequired = 421,
    IntervalTooBrief = 423,
    TemporarilyUnavailable = 480,
    CallTransactionDoesNotExist = 481,
    LoopDetected = 482,
    TooManyHops = 483,
    AddressIncomplete = 484,
    Ambiguous = 485,
    BusyHere = 486,
    RequestTerminated = 487,
    NotAcceptableHere = 488,
    RequestPending = 491,
    Undecipherable = 493,
    /* Server Failure */
    ServerInternalError = 500,
    NotImplemented = 501,
    BadGateway = 502,
    ServiceUnavailable = 503,
    ServerTimeout = 504,
    VersionNotSupported = 505,
    MessageTooLarge = 513,
    /* Global Failures */
    BusyEverywhere = 600,
    Decline = 603,
    DoesNotExistAnywhere = 604,
    NotAcceptableGlobal = 606,
};

//! Converts a status code to a string
PROXSIP_API const char* GetSipStatusCodeStr(ESipStatusCode);

//! Converts the number to a status code enumeration if it's valid, or #ESipStatusCode::Unknown otherwise
PROXSIP_API ESipStatusCode SipValidadeStatusCode(unsigned short);

#endif