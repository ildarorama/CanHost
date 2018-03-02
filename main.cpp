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

using namespace std;

namespace pt = boost::property_tree;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

pt::ptree conf;


Module *module;
int main() {
  HttpServer server;
  server.config.port = 8081;


    module=new Module("test");
    Card* card=new Card(module,1);

    CanBusIO io;
    io.start();


  server.resource["^/api$"]["POST"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
     try {
         pt::ptree data;
         pt::ptree data2;
         pt::read_json(request->content, data);

         conf.put("ette",2);
         conf.put("ewqeq.dsfsdf",232);


         //basic_ostream os=response->put('');

         //pt::write_json(response->put(' '),conf);

         std::stringstream ss;


         pt::write_json(ss,conf,true);


         //auto name=pt.get<string>("test");

         response->write(ss);
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
      auto web_root_path = boost::filesystem::canonical("../web");
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

  server.on_error = [](shared_ptr<HttpServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
    // Handle errors here
  };

  thread server_thread([&server]() {
    // Start server
    server.start();
  });

  server_thread.join();
}
