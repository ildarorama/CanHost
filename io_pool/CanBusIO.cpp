//
// Created by Ильдар Сулейманов on 02.03.2018.
//
#include <boost/thread/thread.hpp>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#ifdef USE_CAN
#include <linux/can.h>
#include <linux/can/raw.h>
#endif

#include <glog/logging.h>
#include <iostream>
#include "CanBusIO.h"
#include "../utils/Settings.h"


bool CanBusIO::initIpBus() {
    if ((_socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        return false;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( Settings::Instance().can_bus_proxy_port() );

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

    LOG(INFO) << "Create can socket...";
    if((_socket_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        PLOG(ERROR) << "Error while opening can socket: ";
        perror("Error while opening socket");
        return false;
    }

    strcpy(ifr.ifr_name, Settings::Instance().can_bus_iface().c_str());
    ioctl(_socket_fd, SIOCGIFINDEX, &ifr);
    addr.can_family  = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    LOG(INFO) << "Bind can socket to interface: " << Settings::Instance().can_bus_iface();
    if(bind(_socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        PLOG(ERROR) << "Error in can socket bind: ";
        return false;
    }
    return true;

}

void CanBusIO::sendCanPacket() {
    struct can_frame frame;
    write(_socket_fd,&frame, sizeof (struct can_frame));
}

#endif

void CanBusIO::sendIpPacket() {
    struct sockaddr_in address;
    memset(&address, '\0', sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(inet_addr(Settings::Instance().can_bus_proxy_host().c_str()));
    address.sin_port = htons(Settings::Instance().can_bus_proxy_port());

    PCHECK( sendto(_socket_fd,"123",sizeof(3),0,(const sockaddr*) &address,sizeof(address)) )  << "Can not send udp message: " ;
}

void CanBusIO::_pool_func() {
#ifdef USE_CAN
    while(! initCanBus() ) {
       boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
#else
    while(! initIpBus() ) {
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
#endif

    while(_running) {
        std::cout << "Tick....\n";
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
#ifdef USE_CAN
        sendCanPacket();
#else
        sendIpPacket();
#endif
    }
}


void CanBusIO::start() {
    boost::thread(&CanBusIO::_pool_func,this);
}

CanBusIO::CanBusIO() {
    _running=true;
}

