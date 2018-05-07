cmake_minimum_required(VERSION 3.0)

project(CanHost)

#find_package(Protobuf REQUIRED)
set(Protobuf_INCLUDE_DIR,"hid_io")
set(Protobuf_LIBRARIES,"/usr/local/Cellar/protobuf@2.6/2.6.0/lib/libprotobuf.dylib")

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()


file(GLOB hardware
        "hardware/*.h"
        "hardware/*.cpp"
        "context/*.h"
        "context/*.cpp"
        "utils/*.h"
        "utils/*.cpp"
        "io_pool/*.h"
        "io_pool/*.cpp"
        "hid_io/*.h"
        "hid_io/*.cc"
        "hid_io/*.hpp"
        "hid_io/*.cpp"
        "webserver/*.h"
        "webserver/*.cpp")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY objects)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY objects)

add_definitions("-Wno-deprecated -g")


link_libraries(boost_iostreams boost_filesystem boost_system boost_thread-mt boost_date_time-mt glog pthread dl zmq protobuf)
include_directories("/usr/local/opt/protobuf@2.6/include" "/usr/local/include")
link_directories("/usr/local/opt/protobuf@2.6/lib" "/usr/local/lib")

if(LINUX)
    add_executable(CanProxy can_proxy/proxy.c)
    target_link_libraries(CanProxy pthread)
    add_definitions("-DUSE_CAN")
endif()

add_library(CanHostObject STATIC ${hardware})
add_executable(CanHost main.cpp ${hardware})

target_compile_options(CanHost PUBLIC "-std=c++11")
set_target_properties(CanHostObject
            PROPERTIES
            CMAKE_RUNTIME_OUTPUT_DIRECTORY "../objects"
        )
target_compile_options(CanHostObject PUBLIC "-std=c++11")


ADD_SUBDIRECTORY(scripts)
