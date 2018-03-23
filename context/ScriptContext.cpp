//
// Created by Ильдар Сулейманов on 19.03.2018.
//

#include "ScriptContext.h"

ScriptContext &ScriptContext::Instance() {
    static ScriptContext _instance;
    return _instance;
}

ScriptContext::ScriptContext() {
}

Card *ScriptContext::card(int slot) {
    return _cards.at(slot);
}
