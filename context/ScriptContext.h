//
// Created by Ильдар Сулейманов on 19.03.2018.
//

#ifndef CANHOST_SCRIPTCONTEXT_H
#define CANHOST_SCRIPTCONTEXT_H


#include "../hardware/Card.h"
#include "../hardware/ChannelAlias.h"
#include "../hardware/Module.h"
#include "ScriptLine.h"
#include <glog/logging.h>
#include <string>
#include <map>

class ScriptLine;
class ScriptContext {

public:
    static ScriptContext& Instance();
    void setModule(Module * module);
    Module *module();
    Card* card(int slot);
    void putAlias(std::string alias, ChannelAlias channel);
    std::string hasAlias(int card,int device, int channel);
    bool hasAlias(std::string alias);
    void log(const char* format, ...);
    google::NullStream::basic_ostream& log();
    void wait(unsigned int ms);
    ScriptLine& line();
private:
    std::vector<Card *> _cards;
    std::map<std::string,ChannelAlias> aliases;
    ScriptContext();
    ScriptContext(ScriptContext const&) = delete;
    Module *_module=nullptr;
};


#endif //CANHOST_SCRIPTCONTEXT_H
