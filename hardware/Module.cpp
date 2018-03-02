//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#include "Module.h"
#include "boost/log/trivial.hpp"


Module::Module(std::string n):module_name(n) {
    BOOST_LOG_TRIVIAL(trace) << "Create module.... " << name();
}