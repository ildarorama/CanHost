//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#include <glog/logging.h>
#include "Module.h"


Module::Module(std::string n):module_name(n) {
    LOG(INFO) << "Create module " << n;
}

std::string Module::name() {
    return "sd";
}