//
// Created by Ильдар Сулейманов on 02.03.2018.
//
#include <boost/thread/thread.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include <glog/logging.h>
#include <iostream>
#include "CanBusIO.h"


bool CanBusIO::initIpBus() {
    if ((_socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        return false;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( 5557 );

    int rc= bind(_socket_fd, (struct sockaddr *) &address, sizeof(address) );
    if ( rc < 0 ) {
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

    if(bind(_socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Error in socket bind");
        return -2;
    }

}
#endif

void CanBusIO::sendPacket() {
    struct sockaddr_in address;
    memset(&address, '\0', sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(inet_addr("192.168.1.1"));
    address.sin_port = htons(5555);

    PCHECK( sendto(_socket_fd,"123",sizeof(3),0,(const sockaddr*) &address,sizeof(address)) )  << "Can not send udp message: " ;
}

void CanBusIO::_pool_func() {
    while(! initIpBus() ) {
       boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }

    while(_running) {
        std::cout << "Tick....\n";
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
        sendPacket();
    }
}


void CanBusIO::start() {
    boost::thread(&CanBusIO::_pool_func,this);
}

CanBusIO::CanBusIO() {
    _running=true;
}

