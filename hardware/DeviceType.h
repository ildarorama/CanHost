//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_DEVICETYPE_H
#define CANHOST_DEVICETYPE_H

#include <string>


class DeviceType {

public:
    DeviceType(std::string name);
    DeviceType(const DeviceType&) = default;
    static DeviceType DIGITAL_OUTPUT_32_CHANNEL;
    static DeviceType DIGITAL_INPUT_32_CHANNEL;
private:
    const std::string _name;

};



#endif //CANHOST_DEVICETYPE_H
