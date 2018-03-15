//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_MODULE_H
#define CANHOST_MODULE_H

#include <string>


class Module {
private:
    std::string module_name;
public:
    Module(std::string);
    std::string name();
    void test();
};


#endif //CANHOST_MODULE_H
