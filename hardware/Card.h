//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_CARD_H
#define CANHOST_CARD_H

#include <vector>
#include <map>

#include "Device.h"



class Card {
private:
    std::map<int,Device*> _devices;
    const int _slot;
public:
    Card(const int slot);
    const int slot();
    Device * device(int idx=0);
    void putDevice(Device *device,const int idx);

};




#endif //CANHOST_CARD_H
