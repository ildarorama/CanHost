//
// Created by Ильдар Сулейманов on 19.03.2018.
//

#ifndef CANHOST_SCRIPTEXCEPTION_H
#define CANHOST_SCRIPTEXCEPTION_H


#include <exception>
#include <string>

class ScriptException : public std::exception {
public:
    ScriptException(std::string message);
private:
    std::string _message;
};


#endif //CANHOST_SCRIPTEXCEPTION_H
