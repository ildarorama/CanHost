//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#include <iostream>
#include "DiscreteOutputDevice.h"

DiscreteOutputDevice::DiscreteOutputDevice(Card& card, int address) : Device(card, address) {

    for(int i=0;i<32;i++) {

        DiscreteOutputChannel p(i);

        _channels.push_back(p);

    }
    std::cout << _channels.at(0).offset() << std::endl;
}

void DiscreteOutputDevice::changeStateRequestListener(bool oldState, bool newState, int offset) {

}

DiscreteOutputChannel& DiscreteOutputDevice::channel(int channel) {
    return _channels.at(channel);
}

