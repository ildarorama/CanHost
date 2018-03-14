//
// Created by Ильдар Сулейманов on 13.03.2018.
//

#ifndef CANHOST_DISCRETEOUTPUTCHANNEL_H
#define CANHOST_DISCRETEOUTPUTCHANNEL_H


#include "Device.h"
#include "DiscreteOutputDevice.h"

class DiscreteOutputChannel {
public:
    DiscreteOutputChannel(int offset,std::function<void(const DiscreteOutputDevice*, bool,bool,int)> listener);
    bool state();
    bool state(bool state);
private:
    int _offset;
    bool _state=false;
    std::function<int(const DiscreteOutputDevice&, bool,bool,int)> _listener;
};


#endif //CANHOST_DISCRETEOUTPUTCHANNEL_H
