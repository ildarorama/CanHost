//
// Created by Ильдар Сулейманов on 13.03.2018.
//

#include <iostream>
#include "DiscreteOutputChannel.h"

DiscreteOutputChannel::DiscreteOutputChannel(int offset) :
        _offset(offset) {

}

bool DiscreteOutputChannel::state() {
    return _state;
}

bool DiscreteOutputChannel::state(bool state) {
    if ( _state != state ) {
        //_listener(_state,state,_offset);
    }
    return _state=state;
}

DiscreteOutputChannel::~DiscreteOutputChannel() {
    std::cout << "Destroy channel " << _offset << std::endl;
}

int DiscreteOutputChannel::offset() {
    return _offset;
}

DiscreteOutputChannel::DiscreteOutputChannel(const DiscreteOutputChannel &o) {
    *this=o;
    std::cout << "Copy channel " << _offset << std::endl;

}

//DiscreteOutputChannel::DiscreteOutputChannel(const DiscreteOutputChannel &) {
//    std::cout << "copy channel" << _offset << std::endl;
//}
