//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#include "DiscreteOutputDevice.h"

DiscreteOutputDevice::DiscreteOutputDevice(Card& card, int address) : Device(card, address, DeviceType::DIGITAL_OUTPUT_32_CHANNEL) {

    for(int i=0;i<32;i++) {

        DiscreteOutputChannel p=DiscreteOutputChannel::DiscreteOutputChannel(i);

        _channels.push_back(&p);

    }
}

void DiscreteOutputDevice::changeStateRequestListener(bool oldState, bool newState, int offset) {

}

