#include "server.hpp"

#include <Arduino.h>

ws::Server::Server(unsigned int port, cstr ssid, cstr password):
    web_(port),
    ssid_(ssid),
    password_(password),
    one_()
{}

void ws::Server::connect()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid_, password_);
}

bool ws::Server::is_connected()
{
    return WiFi.status() == WL_CONNECTED;
}

void ws::Server::begin()
{
    web_.begin();
}

void ws::Server::setup_one_page(cstr link, const PageType & rhs)
{
    one_ = rhs;
    web_.on(link, HTTP_GET, [this](AsyncWebServerRequest * request)
    {
        request->send(one_.code, one_.type, one_.update());
    });
}
