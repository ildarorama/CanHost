//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#include "Module.h"
#include <glog/logging.h>


Module::Module(std::string n):module_name(n) {
    LOG(INFO) << " Test ";
}