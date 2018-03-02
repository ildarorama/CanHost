//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_DISCRETEOUTPUT_H
#define CANHOST_DISCRETEOUTPUT_H


#include "Device.h"

class DiscreteOutput: public Device {
public:
    DiscreteOutput(Card *card,int address);
};


#endif //CANHOST_DISCRETEOUTPUT_H
