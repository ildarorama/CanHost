//
// Created by Ильдар Сулейманов on 21.03.2018.
//

#include <iostream>
#include "Channel.h"
#include "../context/ScriptException.h"

Channel::Channel(const int num, DeviceClass deviceClass) : _num(num), _deviceClass(deviceClass) {

}

int Channel::encoder() {
    if (_deviceClass != DeviceClass::ENCODER ) throw ScriptException("Incorrect port type");
    return 0;
}


double Channel::analogInput() {
    if (_deviceClass != DeviceClass::ANALOG_INPUT ) throw ScriptException("Incorrect port type");
    return 0;
}


void Channel::output(const double val) { analogOutput(val); }
void Channel::analogOutput(const double val) {
    if (_deviceClass != DeviceClass::ANALOG_OUTPUT ) throw ScriptException("Incorrect port type");
}

bool Channel::input() {
    if (_deviceClass != DeviceClass::DIGITAL_INPUT ) throw ScriptException("Incorrect port type");
    return true;
}

void Channel::output(const bool val) {
    if (_deviceClass != DeviceClass::DIGITAL_OUTPUT ) throw ScriptException("Incorrect port type");
    std::cout << "Output to the device" << _num << std::endl;
}

DeviceClass Channel::deviceClass() {
    return _deviceClass;
}
