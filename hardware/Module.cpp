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

void Module::addAlias(std::string alias, Channel *channel) {
    _aliases.insert(std::pair<std::string,Channel *>(alias,channel));
}

Channel *Module::alias(std::string alias) {
    return _aliases.at(alias);
}

void Module::addCard(Card *card) {
    _cards.insert(std::pair<int,Card *>(card->slot(),card));
}
