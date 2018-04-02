//
// Created by  Ильдар Сулейманов on 13.03.2018.
//

#include "ZeroMqServer.h"

#import "zmq.hpp"


#include <iostream>
#include <glog/logging.h>
#include "message.pb.h"

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
    Telemetry t;
    double z=1.3;
    while(true) {




        if (s.recv(m,ZMQ_DONTWAIT)) {
            std::cout << "Receive new packet " << std::endl;

            if ( t.ParseFromArray(m->data(),m->size()) ) {
                std::cout << "Seq: " << t.seq() << std::endl;
            }

            Telemetry t;
            t.set_seq(2);
            t.mutable_state()->set_acord(z++);
            t.mutable_state()->set_bcord(z++);
            t.mutable_state()->set_ccord(z++);
            t.mutable_state()->set_xcord(z++);
            t.mutable_state()->set_ycord(z++);
            t.mutable_state()->set_zcord(z++);




            zmq::message_t m(t.ByteSize());
            if ( t.SerializeToArray(m.data(),m.size()) ) {
                std::cout << "Sending packet " << std::endl;
                s.send(m,0);
            }
        }



        //boost::this_thread::sleep_for(boost::chrono::seconds(5));
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
