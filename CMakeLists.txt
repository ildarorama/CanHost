cmake_minimum_required(VERSION 3.0)

project(CanHost)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY objects)
#include_directories(/usr/local/opt/boost@1.66/include)
#link_directories(/usr/local/opt/boost@1.66/lib)
link_libraries(boost_iostreams boost_filesystem boost_system boost_thread-mt glog pthread)

add_compile_options("-std=c++11")
#add_definitions("-DUSE_CAN")

add_library(CanHostObject STATIC hardware/Module.cpp hardware/Module.h hardware/Card.cpp hardware/Card.h hardware/Device.cpp hardware/Device.h utils/Utils.cpp utils/Utils.h hardware/DiscreteOutput.cpp hardware/DiscreteOutput.h hardware/DiscreteInput.cpp hardware/DiscreteInput.h hardware/DeviceType.cpp hardware/DeviceType.h io_pool/CanBusIO.cpp io_pool/CanBusIO.h utils/Settings.cpp utils/Settings.h)

add_executable(CanHost main.cpp hardware/Module.cpp hardware/Module.h hardware/Card.cpp hardware/Card.h hardware/Device.cpp hardware/Device.h utils/Utils.cpp utils/Utils.h hardware/DiscreteOutput.cpp hardware/DiscreteOutput.h hardware/DiscreteInput.cpp hardware/DiscreteInput.h hardware/DeviceType.cpp hardware/DeviceType.h io_pool/CanBusIO.cpp io_pool/CanBusIO.h utils/Settings.cpp utils/Settings.h webserver/WebServer.cpp webserver/WebServer.h webserver/StatusCode.h webserver/SimpleServer.h webserver/ServerUtility.h)


