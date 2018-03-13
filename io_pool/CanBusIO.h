//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_CANBUSIO_H
#define CANHOST_CANBUSIO_H



#include <boost/thread/thread.hpp>
#include <boost/lockfree/queue.hpp>
#include "CanMessage.h"

class CanBusIO final {
public:
    CanBusIO();
    void start();
    void sendMessage(const CanMessage& message);
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
    boost::lockfree::queue<CanMessage> _queue;
};


#endif //CANHOST_CANBUSIO_H
