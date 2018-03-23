//
// Created by Ильдар Сулейманов on 19.03.2018.
//

#ifndef CANHOST_SCRIPTCONTEXT_H
#define CANHOST_SCRIPTCONTEXT_H


#include "../hardware/Card.h"
#include <string>

class ScriptContext {

public:
    static ScriptContext& Instance();

    Card* card(int slot);

private:
    std::vector<Card *> _cards;
    ScriptContext();
    ScriptContext(ScriptContext const&) = delete;
};


#endif //CANHOST_SCRIPTCONTEXT_H
