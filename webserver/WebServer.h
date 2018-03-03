//
// Created by Ильдар Сулейманов on 03.03.2018.
//

#ifndef CANHOST_WEBSERVER_H
#define CANHOST_WEBSERVER_H

#include "../webserver/SimpleServer.h"
#include "../webserver/StatusCode.h"

#include <boost/filesystem.hpp>

namespace WebServer {

    class WebServer {
    private:
        WebServer();

        WebServer(WebServer const &) = delete;
        WebServer &operator=(WebServer const &) = delete;

        void apiHandler(std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response, std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request);

        void staticHandler(std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response, std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request);

        SimpleWeb::Server<SimpleWeb::HTTP> _server;

        void init();

    public:
        static WebServer &Instance();
        void start();
    };
}

#endif //CANHOST_WEBSERVER_H
