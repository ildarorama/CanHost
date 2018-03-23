//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_DEVICE_H
#define CANHOST_DEVICE_H


#include <vector>
#include "DeviceType.h"
#include "Channel.h"

class Device {
private:
    DeviceType &_deviceType;
    int _address;
    int _fw_version_minor;
    int _fw_version_major;


    std::vector<Channel *> _channels;
public:
    int address();
    const DeviceType &deviceType();
    Device(int address,DeviceType &deviceType);

    Channel * channel(const int idx);
    void addChannel(Channel *);

    std::string fw_version();
};



#endif //CANHOST_DEVICE_H
