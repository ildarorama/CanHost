cmake_minimum_required(VERSION 3.0)

project(CanHostPlugin)

file(GLOB plugins
        "m0.cpp"
        )

set(CMAKE_CXX_STANDARD 11)
set(LIBRARY_OUTPUT_DIRECTORY "../plugin")
link_libraries(boost_iostreams boost_filesystem boost_system boost_thread-mt glog pthread)

add_compile_options("-std=c++11")

add_library("m0" SHARED "m0.cpp")

#target_link_libraries(${PLUGIN_NAME} ${CMAKE_SOURCE_DIR}/../objects/libCanHostObject.a)
