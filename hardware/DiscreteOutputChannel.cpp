//
// Created by Ильдар Сулейманов on 13.03.2018.
//

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