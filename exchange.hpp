#ifndef EXCHANGE_HPP
#define EXCHANGE_HPP

#include <w-struct.hpp>

namespace ws
{
    class Exchanger
    {
        public:
            Exchanger() = delete;
            Exchanger(MACADDR addr);
            Exchanger(const Exchanger &) = delete;
            Exchanger(Exchanger &&) = delete;
            Exchanger operator=(const Exchanger &) = delete;
            Exchanger operator=(Exchanger &&) = delete;
            ~Exchanger() = default;

            bool init();
            void send(const YOUR_STRUCT & data);
            YOUR_STRUCT & recv();
            
        private:
            MACADDR addr_;
    };
}

#endif
