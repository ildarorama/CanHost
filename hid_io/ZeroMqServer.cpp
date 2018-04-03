//
// Created by  Ильдар Сулейманов on 13.03.2018.
//

#include "ZeroMqServer.h"

#import "zmq.hpp"


#include <iostream>
#include <glog/logging.h>
#include "message.pb.h"
#include "../utils/Settings.h"

ZeroMqServer &ZeroMqServer::Instance() {
    static ZeroMqServer s;
    return s;
}

ZeroMqServer::ZeroMqServer() {

}

static void sendTelemetry(zmq::socket_t &s, Telemetry &t) {
    zmq::message_t m(t.ByteSize());

    if ( t.SerializeToArray(m.data(),m.size()) ) {
        LOG(INFO) << "Send telemetry " << RequestType_Name(t.type());
        s.send(m,0);
    }
}

void ZeroMqServer::_server_func() {
    LOG(INFO) << "Create ZeroMQ server!";
    zmq::context_t c(3);
    zmq::socket_t s(c,zmq::socket_type::pair);
    s.setsockopt(ZMQ_RCVTIMEO,2000);

    s.bind("tcp://0.0.0.0:7777");


    int32_t seq=1;

    zmq::message_t *m=new zmq::message_t(10000);
    Telemetry t;
    double z=1.3;
    while(_running) {

        if (s.recv(m,0)) {

            if ( t.ParseFromArray(m->data(),m->size()) ) {
                LOG(INFO) << "Receive ZMQ telemetry type: " << RequestType_Name(t.type());

                if ( t.type() == RequestType::Ping ) {
                    Telemetry t;
                    t.set_seq(seq++);
                    t.set_type(RequestType::Pong);
                    sendTelemetry(s,t);
                }

                if ( t.type() == RequestType::ConfigRequest ) {
                    Telemetry t;
                    t.set_seq(seq++);
                    t.set_type(RequestType::ConfigResponse);
                    t.mutable_config()->set_version(Settings::Instance().version());
                    t.mutable_config()->set_config(Settings::Instance().config());
                    sendTelemetry(s,t);
                }

                if ( t.type() == RequestType::CodeListRequest ) {
                    t.set_seq(seq++);
                    t.set_type(RequestType::CodeListResponse);
                    Code *c=t.mutable_codelist()->Add();
                    c->set_name("123");
                    c->set_body("G1\nG2\nG5");
                    c=t.mutable_codelist()->Add();
                    c->set_name("456");
                    c->set_body("G4\nG5\nG2");
                    c=t.mutable_codelist()->Add();
                    c->set_name("35454");
                    c->set_body("G4\nG1\nG4");
                    sendTelemetry(s,t);
                }

                if ( t.type() == RequestType::TelemtryRequest ) {
                    Telemetry t;
                    t.set_seq(seq++);
                    t.set_type(RequestType::TelemetryResponse);
                    t.mutable_state()->set_acord(z++);
                    t.mutable_state()->set_bcord(z++);
                    t.mutable_state()->set_ccord(z++);
                    t.mutable_state()->set_xcord(z++);
                    t.mutable_state()->set_ycord(z++);
                    t.mutable_state()->set_zcord(z++);
                    sendTelemetry(s,t);
                }

                if ( t.type() == RequestType::PushButtonRequest ) {
                    LOG(INFO) << "Receive packet PushButtonRequest " << t.pushbutton().name() << " state: " << t.pushbutton().state();
                }

            }
        } else {
            LOG(INFO) << "No data. Sending ping request";
            Telemetry t;
            t.set_seq(seq++);
            t.set_type(RequestType::Ping);
            sendTelemetry(s,t);
        }
    }
}

void ZeroMqServer::stop() {
    _running=false;
    _worker->join();
}

void ZeroMqServer::start() {

    _worker=new boost::thread(&ZeroMqServer::_server_func,this);

}
