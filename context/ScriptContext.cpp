//
// Created by Ильдар Сулейманов on 19.03.2018.
//

#include "ScriptContext.h"
#include "../hardware/ChannelAlias.h"

ScriptContext &ScriptContext::Instance() {
    static ScriptContext _instance;
    return _instance;
}

ScriptContext::ScriptContext() {
}

Card *ScriptContext::card(int slot) {
    return _cards.at(slot);
}

void ScriptContext::putAlias(std::string alias, ChannelAlias channel) {
    aliases.insert(std::pair<std::string,ChannelAlias>(alias,channel));
}

void ScriptContext::setModule(Module *module) {
    _module=module;
}

Module *ScriptContext::module() {
    return _module;
}

std::string &ScriptContext::hasAlias(int card, int device, int channel) {
    std::map<std::string,ChannelAlias>::iterator it;

    for(it=aliases.begin(),it != aliases.end();it++) {
        ChannelAlias alias=it.
    }
    return <#initializer#>;
}
