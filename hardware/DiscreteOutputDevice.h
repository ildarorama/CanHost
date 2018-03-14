//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_DISCRETEOUTPUT_H
#define CANHOST_DISCRETEOUTPUT_H


#include "Device.h"
#include "DiscreteOutputChannel.h"


#include <vector>
#include <map>

class DiscreteOutputDevice: public Device {
public:
    DiscreteOutputDevice(Card *card,int address);
    void changeStateRequestListener(bool oldState,bool newState,int address);
private:
    std::vector<const DiscreteOutputChannel &> _channels;
};


#endif //CANHOST_DISCRETEOUTPUT_H
