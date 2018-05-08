//
// Created by  Ильдар Сулейманов on 08.05.2018.
//

#include "ScriptLine.h"

ScriptLine::ScriptLine(ScriptContext &ctx) :
    _ctx(ctx) {
}

double ScriptLine::getArgAsDouble(int num,double def) {
    if ( _args.size()>num ) { return def; }
    return std::stod(_args.at(num-1));
}

int ScriptLine::getArgAsInt(int num,int def) {
    if ( _args.size()>num ) { return def; }
    return std::stoi(_args.at(num-1));
}

std::string ScriptLine::getArgAsString(int num,std::string def) {
    if ( _args.size()>num ) { return def; }
    return _args.at(num-1);
}

ScriptLine& ScriptLine::wait(int ms) {
    _ctx.wait(ms);
    return _ctx.line();
}

bool ScriptLine::hasArg(int num) {
    return _args.size()<=num;
}

void ScriptLine::setArgs(std::string args) {
    args.clear();
    std::stringstream s(args);
    while(!s.eof()) {
        std::string tmp;
        s >> tmp;
        _args.push_back(tmp);
    }
}