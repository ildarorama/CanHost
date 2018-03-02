cmake_minimum_required(VERSION 3.7)


project(CanHost)

set(CMAKE_CXX_STANDARD 11)
include_directories("/usr/local/opt/boost@1.60/include" "/usr/local/Cellar/glog/0.3.5_3/include")
link_directories("/usr/local/opt/boost@1.60/lib" "/usr/local/Cellar/glog/0.3.5_3/lib")
link_libraries(boost_iostreams boost_filesystem boost_system boost_thread-mt glog)

find_library (LIBSTDCXX NAMES stdc++)

add_executable(CanHost main.cpp hardware/Module.cpp hardware/Module.h hardware/Card.cpp hardware/Card.h hardware/Device.cpp hardware/Device.h utils/Utils.cpp utils/Utils.h hardware/DiscreteOutput.cpp hardware/DiscreteOutput.h hardware/DiscreteInput.cpp hardware/DiscreteInput.h hardware/DeviceType.cpp hardware/DeviceType.h io_pool/CanBusIO.cpp io_pool/CanBusIO.h)