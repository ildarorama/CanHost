//
// Created by Ильдар Сулейманов on 13.03.2018.
//

#ifndef CANHOST_DISCRETEOUTPUTCHANNEL_H
#define CANHOST_DISCRETEOUTPUTCHANNEL_H


#include "Device.h"
#include "DiscreteOutputDevice.h"
#include <functional>

class DiscreteOutputChannel {
public:
    DiscreteOutputChannel(int offset);
    bool state();
    bool state(bool state);
private:
    int _offset;
    bool _state=false;

};


#endif //CANHOST_DISCRETEOUTPUTCHANNEL_H
