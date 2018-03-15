//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_CARD_H
#define CANHOST_CARD_H


#include "Module.h"

class Card {
private:
    Card(const Module *m, const int slot);

    int _slot;
    Module* _module;
public:
    Card(Module * m,const int c);
    const int slot();

};


#endif //CANHOST_CARD_H
