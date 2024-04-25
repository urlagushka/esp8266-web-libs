# WEB libraries for ESP8266

## server.hpp // using namespace ws
---
This library for creating a web page.
Server library including:
* ESPAsyncWebServer.h
* ESP8266WiFi.h
* ESPAsyncTCP.h
* w-struct.hpp

Example of creating:
```cpp
#include <server.hpp> // ws::Server

ws::Server web(port, "ssid", "password");
```
Connection in setup() method:
```cpp
#include <server.hpp> // ws::Server

ws::Server web(port, "ssid", "password");

void setup()
{
    web.connect();
    bool conn_status = web.is_connected();
    
    web.begin();
}
```
Setup page in setup() method:
```cpp
#include <server.hpp> // ws::Server
#include <w-struct.hpp> // ws::PageType
#include <pages.hpp> // page::about()

ws::Server web(port, "ssid", "password");

void setup()
{
    web.connect();
    bool conn_status = web.is_connected();
    
    // creating a ws::PageType object with opcode 200, page type "text/html", page content from page::about(), additional function that called on page loads
    ws::PageType about_page__ = {200, "text/html", page::about(), empty};
    // linking about_page__ with "/about" link
    web.setup_page("/about", about_page__);
    
    web.begin();
}
```
Additional function called before page loading and it's possible to modified page, for example:
```cpp
String addf(); // addf signature

String put_info_on_about_page()
{
    String res = "";
    res += "<p>Hi, it's about page!</p>";
    return res;
}
```
#### pages // using namespace page
```cpp
page_t = String (*)(const String &) // page format
```
How to create a page:
```cpp
String my_custom_page(const String & temp)
{
    String res = "<!DOCTYPE HTML><html><head><title>MegaESP</title>";
    res += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    res += "</head><body><h1>MEGA & ESP8266</h1>";
    // your html page content here
    res += temp; // html content from addf

    res += "</body></html>";
    return res;
}

namespace page
{
    page_t my_custom() { return my_custom_page; }
}
```

## exchange.hpp // using namespace ws
---
This is library for communicate between ESP8266 using MAC address.
Exchange library including:
* espnow.h
* w-struct.hpp

Example of creating:
```cpp
#include <exchange.hpp>
ws::MACADDR addr = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
ws::Exchanger exch(addr);
```
Example of using:
```cpp
void setup()
{
    exch.init();
}

void loop()
{
    StructEXC to_send = {1, 1, 0};
    exch.send(to_send);
    
    StructEXC to_recv = exch.recv(); // waiting for data
}
```
You need modify source files for your own struct.
## w-struct.hpp // using namespace ws
---
w-struct.hpp has next structs:
* IPADDR - ip address struct
* MACADDR - mac address struct
* PageType - page struct

It can be used with server.hpp, exchange.hpp
