#ifndef W_STRUCT_HPP
#define W_STRUCT_HPP

#include "Arduino.h"

namespace ws
{
    using cstr = const char *;
    using page_t = String (*)(const String &);

    struct IPADDR
    {
        byte addr[4];
    };

    struct MACADDR
    {
        uint8_t addr[6];
    };

    struct PageType
    {
        unsigned int code;
        cstr type;
        page_t page;
        String (*addf)();

        String update(){ return page(addf()); }
    };
}

#endif
