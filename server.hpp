#ifndef SERVER_HPP
#define SERVER_HPP

#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>

#include "w-struct.hpp"

namespace ws
{
    class Server
    {
        using page_t = String (*)(const String &);
        public:
            Server() = delete;
            Server(unsigned int port, cstr ssid, cstr password);
            Server(const Server &) = delete;
            Server(Server &&) = delete;
            Server operator=(const Server &) = delete;
            Server operator=(Server &&) = delete;
            ~Server() = default;

            void connect();
            bool is_connected();
            void begin();

            void setup_one_page(cstr link, const PageType & rhs);

        private:
            AsyncWebServer web_;
            cstr ssid_;
            cstr password_;
            PageType one_;
    };
}

#endif
