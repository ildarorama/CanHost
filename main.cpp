
#include "hardware/Module.h"
#include "hardware/Card.h"
#include "io_pool/CanBusIO.h"
#include "utils/Settings.h"
#include "webserver/WebServer.h"

#include <glog/logging.h>
#include <dlfcn.h>

Module *module;
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

    CanBusIO* io=new CanBusIO();
    io->start();
    module=new Module("test");
    Card* card=new Card(module,1);



    char *error;
    int (*work)(Module *);
#ifdef USE_CAN
    void* handle = dlopen("plugin/libtestscript.so", RTLD_LAZY);
#else
    void* handle = dlopen("plugin/libtestscript.dylib", RTLD_LAZY);
#endif

    work =(int (*)(Module *)) dlsym(handle, "work");
    if ((error = dlerror()) != NULL)  {
        fprintf (stderr, "%s\n", error);
        exit(1);
    }
    printf ("%d\n", (*work)(module));
    dlclose(handle);

    WebServer::WebServer::Instance().start();
}
