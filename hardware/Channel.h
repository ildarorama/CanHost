//
// Created by Ильдар Сулейманов on 21.03.2018.
//

#ifndef CANHOST_CHANNEL_H
#define CANHOST_CHANNEL_H

enum DeviceClass { ANALOG_OUTPUT, ANALOG_INPUT, DIGITAL_OUTPUT, DIGITAL_INPUT, ENCODER };


class Channel {
public:
    int encoder();
    double analogInput();
    void analogOutput(const double);
    bool input();
    void output(const bool val);
    void output(const double val);
    DeviceClass deviceClass();
    Channel(const int num,DeviceClass deviceClass);
private:

    DeviceClass _deviceClass;
    int _num;
};


#endif //CANHOST_CHANNEL_H
