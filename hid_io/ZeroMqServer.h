//
// Created by  Ильдар Сулейманов on 13.03.2018.
//

#ifndef CANHOST_ZEROMQSERVER_H
#define CANHOST_ZEROMQSERVER_H


#include <boost/thread/thread.hpp>

class ZeroMqServer {
public:
    static ZeroMqServer& Instance();
    void start();
private:
    ZeroMqServer();
    ZeroMqServer(ZeroMqServer const&) = delete;
    ZeroMqServer& operator= (ZeroMqServer const&) = delete;
    void * _context;
    bool _running=true;
    boost::thread* _worker;
    void _server_func();

    void stop();
};


#endif //CANHOST_ZEROMQSERVER_H
