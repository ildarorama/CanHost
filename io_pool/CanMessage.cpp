//
// Created by  Ильдар Сулейманов on 13.03.2018.
//

#include "CanMessage.h"

CanMessage::CanMessage(void *data, int size) :
    _data(data),
    _size(size) {

}

void * CanMessage::data() {
    return _data;
}

int CanMessage::size() {
    return _size;
}
