cmake_minimum_required(VERSION 3.0)

project(CanHostPlugin)

set(CMAKE_CXX_STANDARD 11)
link_libraries(boost_iostreams boost_filesystem boost_system boost_thread-mt glog pthread)

add_compile_options("-std=c++11")

add_library(${PLUGIN_NAME} SHARED ${PLUGIN_NAME}.cpp)

target_link_libraries(${PLUGIN_NAME} ${CMAKE_SOURCE_DIR}/../objects/libCanHostObject.a)
