//
// Created by Ильдар Сулейманов on 02.03.2018.
//
#include <boost/thread/thread.hpp>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "CanBusIO.h"


bool CanBusIO::initIpBus() {
    if ((_socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        return false;
    }

    int opt = 1;
    if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        close(_socket_fd);
        return false;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( 5555 );

    if (bind(_socket_fd, (struct sockaddr *)&address,
             sizeof(address))<0) {
        close(_socket_fd);
        return false;
    }

    return true;
}
#ifdef USE_CAN
bool CanBusIO::initCanBus() {

    struct sockaddr_can addr;
    struct can_frame frame;
    struct ifreq ifr;

    if((_socket_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Error while opening socket");
        return -1;
    }

    strcpy(ifr.ifr_name, ifname);
    ioctl(s, SIOCGIFINDEX, &ifr);

    addr.can_family  = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

    if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Error in socket bind");
        return -2;
    }

}
#endif

void CanBusIO::_pool_func() {
    while(! initIpBus() ) {
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }

    while(! _running) {
        std::cout << "Tick....";
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
}


void CanBusIO::start() {
    boost::thread(&CanBusIO::_pool_func,this);
}

CanBusIO::CanBusIO() {
    _running=true;
}

