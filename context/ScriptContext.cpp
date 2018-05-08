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

ScriptLine& ScriptContext::line() {
    static ScriptLine _line(Instance());
    return _line;
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

void ScriptContext::wait(unsigned int ms) {
    usleep(ms*1000);
}

void ScriptContext::log(const char* format, ...) {
    va_list vl;
    va_start(vl, format);
    auto ret = vprintf(format, vl);
    va_end(vl);
    LOG(INFO) << ret;
}

google::NullStream::basic_ostream& ScriptContext::log() {
    return LOG(INFO);
}

bool ScriptContext::hasAlias(std::string alias) {
    return aliases.count(alias);
}

std::string ScriptContext::hasAlias(int card, int device, int channel) {
    std::map<std::string,ChannelAlias>::iterator it;

    for(it=aliases.begin();it != aliases.end();it++) {

    }
    std::string v=std::string("test");
    return v;
}
