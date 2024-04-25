#include "server.hpp"

#include <Arduino.h>

ws::Server::Server(unsigned int port, cstr ssid, cstr password):
    web_(port),
    ssid_(ssid),
    password_(password),
    test_all_page_(),
    about_page_()
{}

void ws::Server::create_local_point()
{
    const char * ssid = "localKB78";
    const char * password = "12345678";
    IPAddress local_IP(192, 168, 4, 22);
    IPAddress gateway(192, 168, 4, 9);
    IPAddress subnet(255, 255, 255, 0);
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(ssid, password);
}

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

void ws::Server::setup_test_all_page(cstr link, const PageType & rhs)
{
    test_all_page_ = rhs;
    web_.on(link, HTTP_GET, [this](AsyncWebServerRequest * request)
    {
        request->send(test_all_page_.code, test_all_page_.type, test_all_page_.update());
    });
}

void ws::Server::setup_about_page(cstr link, const PageType & rhs)
{
    about_page_ = rhs;
    web_.on(link, HTTP_GET, [this](AsyncWebServerRequest * request)
    {
        request->send(about_page_.code, about_page_.type, about_page_.update());
    });
}

void ws::Server::setup_result_page(cstr link, const PageType & rhs)
{
    result_page_ = rhs;
    web_.on(link, HTTP_GET, [this](AsyncWebServerRequest * request)
    {
        request->send(result_page_.code, result_page_.type, result_page_.update());
    });
}

void ws::Server::setup_status_page(cstr link, const PageType & rhs)
{
    status_page_ = rhs;
    web_.on(link, HTTP_GET, [this](AsyncWebServerRequest * request)
    {
        request->send(status_page_.code, status_page_.type, status_page_.update());
    });
}
