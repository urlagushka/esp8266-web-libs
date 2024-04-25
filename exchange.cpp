#include "exchange.hpp"

#include <Arduino.h>
#include <espnow.h>
#include <w-struct.hpp>

namespace
{
    bool status = false;
    YOUR_STRUCT resp;

    void on_data_send(uint8_t * addr, uint8_t status){}    
    void on_data_recv(uint8_t * addr, uint8_t * data, uint8_t size)
    {
        memcpy(&resp, data, sizeof(resp));
        status = true;
    }
}

ws::Exchanger::Exchanger(MACADDR addr):
    addr_(addr)
{}

bool ws::Exchanger::init()
{
    if (esp_now_init() != 0) return false;
    
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_add_peer(addr_.addr, ESP_NOW_ROLE_COMBO, 1, NULL, 0);

    esp_now_register_send_cb(on_data_send);
    esp_now_register_recv_cb(on_data_recv);
    return true;
}

void ws::Exchanger::send(const YOUR_STRUCT & data)
{
    esp_now_send(addr_.addr, (uint8_t *) &data, sizeof(data));
}

YOUR_STRUCT & ws::Exchanger::recv()
{
    while (!status);
    status = false;
    return resp;
}


