//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#include "Card.h"
#include <glog/logging.h>

Card::Card(Module *m,const int slot):
        _module(m), _slot(slot) {
    LOG(INFO) << "Create card in module " << _module->name();
}

const int Card::slot() {
    return _slot;
}
