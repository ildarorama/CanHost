//
// Created by  Ильдар Сулейманов on 13.03.2018.
//

#include "ZeroMqServer.h"

#import <zmq.h>
#include <glog/logging.h>


ZeroMqServer &ZeroMqServer::Instance() {
    static ZeroMqServer s;
    return s;
}

ZeroMqServer::ZeroMqServer() {

}


void ZeroMqServer::_server_func() {
    while(true) {
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
        LOG(INFO) << "Work thread zeromq ";
    }
}

void ZeroMqServer::stop() {
    _running=false;
    _worker->join();
}

void ZeroMqServer::start() {
    zmq_init(2);
    _context=zmq_ctx_new();
    zmq_msg_t t;


    void * _socket = zmq_socket(_context,ZMQ_PAIR);
    zmq_bind(_socket,"udp://192.168.1.1:5559");
    zmq_recvmsg(_socket,&t,ZMQ_DONTWAIT);
    zmq_send(_socket,"123",3,ZMQ_BACKLOG);
    zmq_close(_socket);

    _worker=new boost::thread(&ZeroMqServer::_server_func,this);

}
