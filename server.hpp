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

            void create_local_point();
            void connect();
            bool is_connected();
            void begin();

            void setup_test_all_page(cstr link, const PageType & rhs);
            void setup_about_page(cstr link, const PageType & rhs);
            void setup_result_page(cstr link, const PageType & rhs);
            void setup_status_page(cstr link, const PageType & rhs);

        private:
            AsyncWebServer web_;
            cstr ssid_;
            cstr password_;
            PageType test_all_page_;
            PageType about_page_;
            PageType result_page_;
            PageType status_page_;
    };
}

#endif
