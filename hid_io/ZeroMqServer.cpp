//
// Created by  Ильдар Сулейманов on 13.03.2018.
//

#include "ZeroMqServer.h"

#import "zmq.hpp"

#include <iostream>
#include <glog/logging.h>


ZeroMqServer &ZeroMqServer::Instance() {
    static ZeroMqServer s;
    return s;
}

ZeroMqServer::ZeroMqServer() {

}


void ZeroMqServer::_server_func() {
    zmq::context_t c(3);
    zmq::socket_t s(c,zmq::socket_type::pair);
    s.bind("tcp://0.0.0.0:7777");

    zmq::message_t *m=new zmq::message_t(10000);
    while(true) {

        s.recv(m,0);
        std::cout << "Receive new packet " << std::endl;
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
        //LOG(INFO) << "Work thread zeromq ";
    }
}

void ZeroMqServer::stop() {
    _running=false;
    _worker->join();
}

void ZeroMqServer::start() {

    _worker=new boost::thread(&ZeroMqServer::_server_func,this);

}
