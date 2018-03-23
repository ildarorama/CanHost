//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_MODULE_H
#define CANHOST_MODULE_H

#include <string>
#include <map>
#include "Channel.h"
#include "Card.h"


class Module {
private:
    std::string module_name;
    std::map<std::string,Channel *> _aliases;
    std::map<int,Card *> _cards;
public:
    Module(std::string);
    std::string name();
    void addAlias(std::string alias,Channel * channel);
    void addCard(Card *);
    Channel * alias(std::string alias);
};


#endif //CANHOST_MODULE_H
