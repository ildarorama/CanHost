//
// Created by Ильдар Сулейманов on 03.03.2018.
//

#ifndef CANHOST_SETTINGS_H
#define CANHOST_SETTINGS_H

#include <string>

class Settings final {
public:
    static Settings& Instance();
    bool load();
    bool createDefault();

    int web_server_port();
    std::string web_path();
    std::string can_bus_iface();
private:
    Settings();
    Settings(Settings const&) = delete;
    Settings& operator= (Settings const&) = delete;

    int _web_port=8080;
    std::string _web_path="web";
    std::string _can_bus_iface="can0";
};


#endif //CANHOST_SETTINGS_H
