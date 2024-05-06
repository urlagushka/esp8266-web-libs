#ifndef EXCHANGE_HPP
#define EXCHANGE_HPP

#include <Arduino.h>
#include <espnow.h>
#include <w-struct.hpp>

namespace ws
{
    template< typename STR >
    class Exchanger
    {
        using str_t = STR;
        public:
            Exchanger() = delete;
            Exchanger(MACADDR addr);
            Exchanger(const Exchanger &) = delete;
            Exchanger(Exchanger &&) = delete;
            Exchanger operator=(const Exchanger &) = delete;
            Exchanger operator=(Exchanger &&) = delete;
            ~Exchanger() = default;

            bool init();
            void send(const STR & data);
            STR & recv();
            
        private:
            static void on_data_send(uint8_t * addr, uint8_t status);   
            static void on_data_recv(uint8_t * addr, uint8_t * data, uint8_t size);

            inline static STR resp_;
            inline static bool status_;
            MACADDR addr_;
    };
}

template< typename STR >
ws::Exchanger< STR >::Exchanger(MACADDR addr):
    addr_(addr)
{
    resp_ = STR();
    status_ = false;
}

template< typename STR >
bool ws::Exchanger< STR >::init()
{
    if (esp_now_init() != 0) return false;
    
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_add_peer(addr_.addr, ESP_NOW_ROLE_COMBO, 1, NULL, 0);

    esp_now_register_send_cb(on_data_send);
    esp_now_register_recv_cb(on_data_recv);
    return true;
}

template< typename STR >
void ws::Exchanger< STR >::send(const STR & data)
{
    esp_now_send(addr_.addr, (uint8_t *) &data, sizeof(data));
}

template< typename STR >
STR & ws::Exchanger< STR >::recv()
{
    while (!status_);
    status_ = false;
    return resp_;
}

template< typename STR >
void ws::Exchanger< STR >::on_data_send(uint8_t * addr, uint8_t status)
{};

template< typename STR >
void ws::Exchanger< STR >::on_data_recv(uint8_t * addr, uint8_t * data, uint8_t size)
{
    memcpy(&resp_, data, sizeof(resp_));
    status_ = true;
}

#endif
