cmake_minimum_required(VERSION 3.0)

project(CanHost)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY objects)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

link_libraries(boost_iostreams boost_filesystem boost_system boost_thread-mt glog pthread dl zmq)
include_directories("/usr/local/include")
link_directories("/usr/local/lib")

if(LINUX)
    add_executable(CanProxy can_proxy/proxy.c)
    target_link_libraries(CanProxy pthread)
    add_definitions("-DUSE_CAN")
endif()

add_library(CanHostObject STATIC hardware/Module.cpp hardware/Module.h hardware/Card.cpp hardware/Card.h hardware/Device.cpp hardware/Device.h utils/Utils.cpp utils/Utils.h hardware/DiscreteOutput.cpp hardware/DiscreteOutput.h hardware/DiscreteInput.cpp hardware/DiscreteInput.h hardware/DeviceType.cpp hardware/DeviceType.h io_pool/CanBusIO.cpp io_pool/CanBusIO.h utils/Settings.cpp utils/Settings.h)

add_executable(CanHost main.cpp hardware/Module.cpp hardware/Module.h hardware/Card.cpp hardware/Card.h hardware/Device.cpp hardware/Device.h utils/Utils.cpp utils/Utils.h hardware/DiscreteOutput.cpp hardware/DiscreteOutput.h hardware/DiscreteInput.cpp hardware/DiscreteInput.h hardware/DeviceType.cpp hardware/DeviceType.h io_pool/CanBusIO.cpp io_pool/CanBusIO.h utils/Settings.cpp utils/Settings.h webserver/WebServer.cpp webserver/WebServer.h webserver/StatusCode.h webserver/SimpleServer.h webserver/ServerUtility.h hid_io/ZeroMqServer.cpp hid_io/ZeroMqServer.h io_pool/CanMessage.cpp io_pool/CanMessage.h)

target_compile_options(CanHost PUBLIC "-std=c++11")
target_compile_options(CanHostObject PUBLIC "-std=c++11")

