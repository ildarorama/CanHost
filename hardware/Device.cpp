//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#include "Device.h"
#include "../context/ScriptException.h"


int Device::address() {
    return 0;
}


std::string Device::fw_version() {
    return std::string(std::to_string(_fw_version_major) + "." + std::to_string(_fw_version_minor));
}

Device::Device(int address, DeviceType &deviceType) :
        _address(address),
        _deviceType(deviceType) {

}

Channel *Device::channel(const int idx) {
    return _channels.at(idx);
}

void Device::addChannel(Channel * channel) {
    _channels.push_back(channel);
}

