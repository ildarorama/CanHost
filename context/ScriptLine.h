//
// Created by  Ильдар Сулейманов on 08.05.2018.
//


#ifndef CANHOST_SCRIPTLINE_H
#define CANHOST_SCRIPTLINE_H

#include "ScriptContext.h"

class ScriptContext;
class ScriptLine {
    friend class ScriptContext;
public:
    double getArgAsDouble(int num,double def);
    int getArgAsInt(int num,int def);
    std::string getArgAsString(int num,std::string def);
    ScriptLine& wait(int ms);
    bool hasArg(int num);
private:
    void setArgs(std::string);

    std::vector<std::string> _args;
    ScriptLine(ScriptContext &);
    ScriptLine(ScriptLine const&) = delete;
    ScriptContext &_ctx;
};


#endif //CANHOST_SCRIPTLINE_H
