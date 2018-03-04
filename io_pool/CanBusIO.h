//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_CANBUSIO_H
#define CANHOST_CANBUSIO_H



#include <boost/thread/thread.hpp>

class CanBusIO final {
public:
    CanBusIO();
    void start();
private:
    int _socket_fd;

#ifdef USE_CAN
    void sendCanPacket();
    bool initCanBus();
#endif
    void sendIpPacket();
    bool initIpBus();
    boost::thread* _worker;
    void _pool_func();
    bool _running;
};


#endif //CANHOST_CANBUSIO_H
