//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_DEVICE_H
#define CANHOST_DEVICE_H


#include "Card.h"
#include "DeviceType.h"

class Device {
private:
    Card* _card;
    DeviceType& _deviceType;
    int _address;
    int _fw_version_minor;
    int _fw_version_major;
public:
    Device(Card *card,int address,const DeviceType& deviceType);
    int address();
    const DeviceType& deviceType();
    std::string fw_version();
};


#endif //CANHOST_DEVICE_H
