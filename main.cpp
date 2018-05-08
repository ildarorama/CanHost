
#include "hardware/Module.h"
#include "hardware/Card.h"
#include "io_pool/CanBusIO.h"
#include "utils/Settings.h"
#include "webserver/WebServer.h"
#include "hid_io/ZeroMqServer.h"
#include "context/ScriptContext.h"


#include <glog/logging.h>
#include <dlfcn.h>
#include <csetjmp>



int main(int argc, char* argv[]) {
    google::InitGoogleLogging("CanHost");
    google::SetLogDestination(google::GLOG_INFO,"logs/CanHost");
    google::SetLogFilenameExtension(".log");
    google::SetStderrLogging(google::GLOG_INFO);



    if (! Settings::Instance().load() ) {
        if (! Settings::Instance().createDefault() ) {
            return 1;
        }
    }

    ScriptContext &SC=ScriptContext::Instance();

    ZeroMqServer::Instance().start();

    CanBusIO* io=new CanBusIO();
    io->start();
    io->sendMessage(new CanMessage((void *)"123",4));



    SC.setModule(new Module("test"));
    Card* card=new Card(1);

    Device *dev=new Device(33,DeviceType::DIGITAL_OUTPUT_32_CHANNEL);

    for(int i=0;i<32;i++) {
        Channel *ch=new Channel(i,DeviceClass::DIGITAL_OUTPUT);
        dev->addChannel(ch);

        if (i == 5) {
            SC.module()->addAlias("ALI",ch);
        }
    }

    std::cout << dev->fw_version() << std::endl;

    card->putDevice(dev,2);

    card->device(2)->channel(2)->output(true);

    SC.module()->alias("ALI")->output(true);

    char *error;
    int (*work)(ScriptContext &ctx,std::string arg);
#ifdef USE_CAN
    void* handle = dlopen("plugin/libtestscript.so", RTLD_LAZY);
#else
    void* handle = dlopen("libCanHostPlugin.dylib", RTLD_NOW|RTLD_LOCAL);
#endif

    work =(int (*)(ScriptContext &ctx,std::string arg)) dlsym(handle, "call");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    std::string line="123";

    std::jmp_buf context;
    if(setjmp(context)) {
        std::cout << "Exception in script " << std::endl;
    } else {
        work(SC, line);
    }
    dlclose(handle);

    WebServer::WebServer::Instance().start();
}
