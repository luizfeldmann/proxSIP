#ifndef _ESDPTYPE_H_
#define _ESDPTYPE_H_

enum class ESdpType : char
{
    Version     = 'v',
    Originator  = 'o',
    SessionName = 's',
    Information = 'i',
    URI         = 'u',
    Email       = 'e',
    Phone       = 'p',
    Connection  = 'c',
    Bandwidth   = 'b',
    TimeZone    = 'z',
    Key         = 'k',
    Attribute   = 'a',
    Time        = 't',
    Repeat      = 'r',
    Media       = 'm',
};

#endif