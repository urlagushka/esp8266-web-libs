#include "exchange.hpp"

#include <Arduino.h>
#include <espnow.h>
#include <pin-test.hpp>
#include <w-struct.hpp>

namespace
{
    bool status = false;
    ws::PinResponse resp;

    void on_data_send(uint8_t * addr, uint8_t status){}    
    void on_data_recv(uint8_t * addr, uint8_t * data, uint8_t size)
    {
        memcpy(&resp, data, sizeof(resp));
        status = true;
    }
}

template< typename EXC >
ws::Exchanger< EXC >::Exchanger(MACADDR addr):
    addr_(addr)
{}

template< typename EXC >
bool ws::Exchanger< EXC >::init()
{
    if (esp_now_init() != 0) return false;
    
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_add_peer(addr_.addr, ESP_NOW_ROLE_COMBO, 1, NULL, 0);

    esp_now_register_send_cb(on_data_send);
    esp_now_register_recv_cb(on_data_recv);
    return true;
}

template< typename EXC >
void ws::Exchanger< EXC >::send(const EXC & data)
{
    esp_now_send(addr_.addr, (uint8_t *) &data, sizeof(data));
}

template< typename EXC >
EXC & ws::Exchanger< EXC >::recv()
{
    while (!status);
    status = false;
    return resp;
}


