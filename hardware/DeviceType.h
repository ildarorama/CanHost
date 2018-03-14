//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_DEVICETYPE_H
#define CANHOST_DEVICETYPE_H


class DeviceType {
public:
    DeviceType(const DeviceType&) = delete;
    static const DeviceType DIGITAL_OUTPUT_32_CHANNEL;
private:
    const std::string _name;
    DeviceType(std::string name);
};


#endif //CANHOST_DEVICETYPE_H
