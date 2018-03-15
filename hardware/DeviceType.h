//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#ifndef CANHOST_DEVICETYPE_H
#define CANHOST_DEVICETYPE_H


class DeviceType {

public:
    DeviceType(const DeviceType&) = delete;
    //static DeviceType& DIGITAL_OUTPUT_32_CHANNEL;
private:
    DeviceType(std::string name);
    const std::string _name;

};


#endif //CANHOST_DEVICETYPE_H
