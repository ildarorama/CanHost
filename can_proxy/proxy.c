#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <linux/can.h>
#include <linux/can/raw.h>

int main(int argc, char* argv[]) {

    struct canfd_frame fr;
    struct sockaddr_in si_other;
    struct sockaddr_in si_me;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;

    int s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    int udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);


    if ( s<0 || udp <0 ) { printf("Can not open socket."); return -1;}
    
    strcpy(ifr.ifr_name, "can0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    bind(s, (struct sockaddr *) &addr, sizeof (addr));


    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(5555);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(udp, (struct sockaddr *) &si_me, sizeof (si_me));

    time_t now = time(0);
    time_t last = now;
    long count = 0;
    long rcount = 0;

    memset((char *) &si_other, 0, sizeof (si_other));

    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(5555);
    si_other.sin_addr.s_addr = inet_addr(argv[1]);
    //si_other.sin_addr.s_addr = inet_addr("172.16.5.4");

    
    fd_set rfds;

    while (1) {

        FD_ZERO(&rfds);
        FD_SET(s, &rfds);
        FD_SET(udp, &rfds);

        struct timeval tv;
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        int retval = select(udp+1, &rfds, NULL, NULL, &tv);

        
        if (FD_ISSET(s, &rfds)) {
            read(s, &frame, sizeof (struct can_frame));
            sendto(udp, &frame, sizeof (struct can_frame), 0, (struct sockaddr*) &si_other, sizeof (si_other));                
            count++;
        }
        
        if (FD_ISSET(udp, &rfds)) {
            recv(udp, &frame, sizeof (struct can_frame), MSG_DONTWAIT);            
            write(s,&frame, sizeof (struct can_frame));
            rcount++;
        }
        now = time(0);        
        if (now != last) {
            if ( count || rcount ) printf("Count: %d, RCount: %d\n", count,rcount);
            last = now;
            count = 0;
            rcount=0;
        }
    }
    return (EXIT_SUCCESS);
}

