//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_DEVICE_H
#define CANHOST_DEVICE_H


#include "Card.h"

class Device {
private:
    Card* _card;
    int _address;
    int _fw_version_minor;
    int _fw_version_major;
public:
    Device(Card *card,int address);
    int address();
    std::string fw_version();
};


#endif //CANHOST_DEVICE_H
