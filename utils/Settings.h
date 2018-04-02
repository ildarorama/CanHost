//
// Created by Ильдар Сулейманов on 03.03.2018.
//

#ifndef CANHOST_SETTINGS_H
#define CANHOST_SETTINGS_H

#include <string>
#include <boost/property_tree/ptree.hpp>

class Settings final {
public:
    static Settings& Instance();
    bool load();
    bool createDefault();

    int web_server_port();
    std::string web_path();
    std::string can_bus_iface();
    int can_bus_speed();
    std::string can_bus_proxy_host();
    int can_bus_proxy_port();
    std::string config();
    int version();
private:
    Settings();
    Settings(Settings const&) = delete;
    Settings& operator= (Settings const&) = delete;



    int _web_port=8080;
    int _can_bus_proxy_port=5555;
    int _version=0;
    std::string _web_path="web";
    std::string _can_bus_iface="can0";
    std::string _can_bus_proxy_host="127.0.0.1";
    int _can_bus_speed=512000;
    boost::property_tree::ptree pt;

};


#endif //CANHOST_SETTINGS_H
