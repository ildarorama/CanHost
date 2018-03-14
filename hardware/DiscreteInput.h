//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_DISCRETEINPUT_H
#define CANHOST_DISCRETEINPUT_H


#include "Device.h"

class DiscreteInput: public Device {
    DiscreteInput(const Card& card, int address);

};


#endif //CANHOST_DISCRETEINPUT_H
