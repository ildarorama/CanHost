//
// Created by  Ильдар Сулейманов on 04.05.2018.
//
#include <string>

#include "../context/ScriptContext.h"


extern "C" int call(ScriptContext &ctx,std::string arg) {
    ctx.Instance().module()->alias("ALI")->output(arg=="1");
    return 0;
}