cmake_minimum_required(VERSION 3.0)

project(CanHostPlugin)

file(GLOB plugins
        "m0.cpp"
        "g04.cpp"
        )

set(CMAKE_CXX_STANDARD 11)
set(LIBRARY_OUTPUT_DIRECTORY "../../")

link_libraries(boost_iostreams boost_filesystem boost_system boost_thread-mt glog pthread)


add_compile_options("-std=c++11")

#target_link_libraries(CanHostPlugin )
#message(${CMAKE_SOURCE_DIR}../../bin)

link_directories(
        ${CMAKE_SOURCE_DIR}/bin
)

foreach( item IN ${plugins})
    add_library(${item} SHARED ${plugins})
    target_link_libraries(${item} LINK_PUBLIC ${CMAKE_SOURCE_DIR}/bin/libCanHostObject.a)
endforeach()

#set_target_properties(CanHostPlugin
        #PROPERTIES
        #CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../"
 #       )

#target_link_libraries(CanHostPlugin LINK_PUBLIC ${CMAKE_SOURCE_DIR}/bin/libCanHostObject.a)
#set_property(TARGET CanHostPlugin PROPERTY
        #IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/bin/libCanHostObject.a)



