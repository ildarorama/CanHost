//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#include <glog/logging.h>

#include "Card.h"
#include "../context/ScriptException.h"


Card::Card(const int slot):
        _slot(slot) {
    LOG(INFO) << "Create card in slot " << _slot;
}

const int Card::slot() {
    return _slot;
}

Device *Card::device(int idx) {
    try {
        Device *dev = _devices.at(idx);
        return dev;
    } catch(std::out_of_range e) {
        throw ScriptException("Device not found ");
    }
}

void Card::putDevice(Device *device, const int idx) {
    _devices.insert(std::pair<int,Device *>(idx,device));
}
