cmake_minimum_required(VERSION 3.7)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

project(CanHost)

set(CMAKE_CXX_STANDARD 11)
include_directories("/usr/local/opt/boost@1.60/include")
link_directories("/usr/local/opt/boost@1.60/lib")
link_libraries(boost_iostreams boost_filesystem boost_system boost_log)


add_definitions("-Wno-deprecated -DBOOST_LOG_DYN_LINK")
add_executable(CanHost main.cpp hardware/Module.cpp hardware/Module.h hardware/Card.cpp hardware/Card.h hardware/Device.cpp hardware/Device.h utils/Utils.cpp utils/Utils.h hardware/DiscreteOutput.cpp hardware/DiscreteOutput.h hardware/DiscreteInput.cpp hardware/DiscreteInput.h hardware/DeviceType.cpp hardware/DeviceType.h io_pool/CanBusIO.cpp io_pool/CanBusIO.h)