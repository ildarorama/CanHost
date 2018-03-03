//
// Created by Ильдар Сулейманов on 03.03.2018.
//
#include "../hardware/Module.h"

extern "C" int work(Module *m) {
    m->test();
    return 0;
}