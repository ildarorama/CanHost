#include "server_http.hpp"
#include "utils/Utils.h"
#include "hardware/Module.h"
#include "hardware/Card.h"
#include "io_pool/CanBusIO.h"

// Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <boost/filesystem.hpp>
#define GLOG_logtostderr 1
#include <glog/logging.h>


#define SERVER_PORT 8081

using namespace std;

namespace pt = boost::property_tree;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

pt::ptree conf;

Module *module;
int main(int argc, char* argv[]) { //(int argc, char* argv[]) {
    google::InitGoogleLogging("CanHost");
    google::SetLogDestination(google::GLOG_INFO,"CanHost");
    google::SetLogFilenameExtension(".log");
    google::SetStderrLogging(google::GLOG_INFO);


    HttpServer server;
    server.config.port = SERVER_PORT;

    CanBusIO* io=new CanBusIO();
    io->start();
    module=new Module("test");
    Card* card=new Card(module,1);


  server.resource["^/api$"]["POST"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
     try {
         LOG(INFO) << "Process REST: " << request->query_string;

//         pt::ptree data;
//         pt::ptree data2;
  //       pt::read_json(request->content, data);

//         conf.put("ette",2);
  //       conf.put("ewqeq.dsfsdf",232);


         //basic_ostream os=response->put('');

         //pt::write_json(response->put(' '),conf);

         //std::stringstream ss;


         //pt::write_json(ss,conf,true);


         //auto name=pt.get<string>("test");

         //response->write("23");
     } catch(const exception &e) {
         response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
     }
  };


  // GET-example simulating heavy work in a separate thread
  //server.resource["^/work$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> /*request*/) {
  //  thread work_thread([response] {
  //    this_thread::sleep_for(chrono::seconds(5));
  //    response->write("Work done");
  //  });
   // work_thread.detach();
  //};

  // It is serve resources
  server.default_resource["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
    try {
      auto web_root_path = boost::filesystem::canonical("web");
      auto path = boost::filesystem::canonical(web_root_path / request->path);
      // Check if path is within web_root_path
      if(distance(web_root_path.begin(), web_root_path.end()) > distance(path.begin(), path.end()) ||
         !equal(web_root_path.begin(), web_root_path.end(), path.begin()))
        throw invalid_argument("path must be within root path");
      if(boost::filesystem::is_directory(path))
        path /= "index.html";


      SimpleWeb::CaseInsensitiveMultimap header;
      header.emplace("Cache-Control", "max-age=0");


      auto ifs = make_shared<ifstream>();
      ifs->open(path.string(), ifstream::in | ios::binary | ios::ate);

      if(*ifs) {

          LOG(INFO) << "Get web query " << path.string();

        auto length = ifs->tellg();
        ifs->seekg(0, ios::beg);

        header.emplace("Content-Length", to_string(length));
        response->write(header);

        class FileServer {
        public:
          static void read_and_send(const shared_ptr<HttpServer::Response> &response, const shared_ptr<ifstream> &ifs) {
            // Read and send 128 KB at a time
            static vector<char> buffer(131072); // Safe when server is running on one thread
            streamsize read_length;
            if((read_length = ifs->read(&buffer[0], static_cast<streamsize>(buffer.size())).gcount()) > 0) {
              response->write(&buffer[0], read_length);
              if(read_length == static_cast<streamsize>(buffer.size())) {
                response->send([response, ifs](const SimpleWeb::error_code &ec) {
                  if(!ec)
                    read_and_send(response, ifs);
                  else
                    cerr << "Connection interrupted" << endl;
                });
              }
            }
          }
        };
        FileServer::read_and_send(response, ifs);
      }
      else
        throw invalid_argument("could not read file");
    }
    catch(const exception &e) {
      response->write(SimpleWeb::StatusCode::client_error_bad_request, "Could not open path " + request->path + ": " + e.what());
    }
  };

  server.on_error = [](shared_ptr<HttpServer::Request> request, const SimpleWeb::error_code & ec) {
    LOG(ERROR) << "Caught error while processing web request: " << request->path << ec.message();
  };

  thread server_thread([&server]() {
    LOG(INFO) << "Starting Web server on port: " << SERVER_PORT;
    server.start();
  });

  server_thread.join();
}
