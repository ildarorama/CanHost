//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#include "Module.h"

#include <glog/logging.h>
#include <iostream>

Module::Module(std::string n):module_name(n) {
    LOG(INFO) << "Create module " << n;
}

std::string Module::name() {
    return "sd";
}

void Module::test() {
    std::cout << "Test is work \n";
}
