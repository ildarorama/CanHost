//
// Created by Ильдар Сулейманов on 03.03.2018.
//

#include "WebServer.h"
#include "../utils/Settings.h"

#include <glog/logging.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


namespace WebServer {
    using namespace std;

    WebServer &WebServer::Instance() {
        static WebServer s;
        return s;
    }

    void WebServer::start() {
        init();
        thread server_thread([this]() {
            LOG(INFO) << "Starting Web server on port: " << Settings::Instance().web_server_port();
            try {
                this->_server.start();
            } catch(std::exception e) {
                LOG(ERROR) << "Caught error while run server: " << e.what();
            }
        });
        server_thread.join();
    }


    void WebServer::init() {
        LOG(INFO) << "Configure http server...";
        _server.config.port = Settings::Instance().web_server_port();
        _server.resource["^/api$"]["POST"] = [this](std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response, std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request) {
            this->apiHandler(response, request);
        };

        _server.resource["^/scripts/(.*cpp)$"]["GET"] = [this](std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response, std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request) {
            this->scriptStaticHandler(response, request);
        };

        _server.default_resource["GET"] = [this](std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response, std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request) {
            this->staticHandler(response, request);
        };
        _server.on_error = [](std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request, const SimpleWeb::error_code &ec) {
            LOG(ERROR) << "Caught error while processing web request: " << request->path << ec.message();
        };

    }

    static void read_and_send(const shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> &response, const shared_ptr<ifstream> &ifs) {
        // Read and send 128 KB at a time
        static vector<char> buffer(131072); // Safe when server is running on one thread
        streamsize read_length;
        if ((read_length = ifs->read(&buffer[0], static_cast<streamsize>(buffer.size())).gcount()) >
            0) {
            response->write(&buffer[0], read_length);
            if (read_length == static_cast<streamsize>(buffer.size())) {
                response->send([response, ifs](const SimpleWeb::error_code &ec) {
                    if (!ec)
                        read_and_send(response, ifs);
                    else
                        cerr << "Connection interrupted" << endl;
                });
            }
        }
    }


    static void createStaticResponse(boost::filesystem::path path,
                                     std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response) {
        SimpleWeb::CaseInsensitiveMultimap header;
        header.emplace("Cache-Control", "max-age=0");

        auto ifs = make_shared<ifstream>();
        ifs->open(path.string(), ifstream::in | ios::binary | ios::ate);

        if (*ifs) {
            LOG(INFO) << "Get script query " << path.string();

            auto length = ifs->tellg();
            ifs->seekg(0, ios::beg);

            header.emplace("Content-Length", to_string(length));
            response->write(header);
            read_and_send(response, ifs);
        } else
            throw invalid_argument("could not read file");
    }

    void WebServer::scriptStaticHandler(std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response,
                                  std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request) {


        auto web_root_path = boost::filesystem::canonical(".");
        auto path = boost::filesystem::canonical(web_root_path / request->path);
        LOG(INFO) << "Try get script file " << path;

        if  (
                distance(web_root_path.begin(), web_root_path.end()) > distance(path.begin(), path.end()) ||
            !equal(web_root_path.begin(), web_root_path.end(), path.begin()) ||
                boost::filesystem::is_directory(path)
            ) throw invalid_argument("path must be within root path");
            createStaticResponse(path,response);
    }

    void WebServer::staticHandler(std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response,
                                  std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request) {
        try {
            auto web_root_path = boost::filesystem::canonical(Settings::Instance().web_path());
            auto path = boost::filesystem::canonical(web_root_path / request->path);
            LOG(INFO) << "Try get resource file " << path;

            // Check if path is within web_root_path
            if (distance(web_root_path.begin(), web_root_path.end()) > distance(path.begin(), path.end()) ||
                !equal(web_root_path.begin(), web_root_path.end(), path.begin())
                ) throw invalid_argument("path must be within root path");
            if (boost::filesystem::is_directory(path)) path /= "index.html";
            createStaticResponse(path,response);
        }
        catch (const exception &e) {
            response->write(SimpleWeb::StatusCode::client_error_bad_request, "Could not open path " + request->path + ": " + e.what());
        }
    }

    void WebServer::apiHandler(std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response,
                               std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request) {
        try {
            LOG(INFO) << "Process REST: " << request->query_string;

            boost::property_tree::ptree pt;
            boost::property_tree::read_json(request->content,pt);
            LOG(INFO) << "Get api request: " <<pt.get<string>("query");


            std::string content=pt.get<string>("content");

            std::ofstream outfile("scripts/testscript.cpp");
            outfile << content;
            outfile.close();

            boost::property_tree::ptree resp;
            resp.put("success",true);


            response->write("{success: true}");

        } catch (const std::exception &e) {
            response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
        }
    }

    WebServer::WebServer() {}
}