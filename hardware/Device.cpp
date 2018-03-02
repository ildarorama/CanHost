//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#include "Device.h"

int Device::address() {
    return _address;
}

std::string Device::fw_version() {
    return std::string(std::to_string(_fw_version_major)+"."+std::to_string(_fw_version_minor));
}

Device::Device(Card *card, int address):
    _card(card),
    _address(address) {

}
