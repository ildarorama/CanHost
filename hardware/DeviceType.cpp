//
// Created by Ильдар Сулейманов on 02.03.2018.
//

#include <string>
#include "DeviceType.h"

DeviceType::DeviceType(std::string name) : _name(name)
{

}
DeviceType DeviceType::DIGITAL_OUTPUT_32_CHANNEL("Output module");
DeviceType DeviceType::DIGITAL_INPUT_32_CHANNEL("Input module");
