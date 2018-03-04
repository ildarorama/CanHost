//
// Created by Ильдар Сулейманов on 03.03.2018.
//
#include "Settings.h"


#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <glog/logging.h>

#define SERVER_CONFIG_FILE "settings.json"

Settings::Settings() {
}

bool Settings::load() {
    LOG(INFO) << "Load server config from " << SERVER_CONFIG_FILE;
    boost::property_tree::ptree pt;
    try {
        boost::property_tree::read_json(SERVER_CONFIG_FILE, pt);
        _web_port=pt.get<int>("web_server_port");
        _web_path=pt.get<std::string>("web_server_path");
        _can_bus_iface=pt.get<std::string>("canbus.iface");
        _can_bus_proxy_host=pt.get<std::string>("canbus.proxy.host");
        _can_bus_proxy_port=pt.get<int>("canbus.proxy.port");
    } catch(boost::property_tree::json_parser_error e) {
        LOG(ERROR) << "Can not load config: " << e.message();
        return false;
    }
    return true;
}

bool Settings::createDefault() {
    LOG(INFO) << "Create default seting file: " << SERVER_CONFIG_FILE;

    boost::property_tree::ptree pt;
    pt.put("web_server_port",_web_port);
    pt.put("web_server_path",_web_path);
    pt.put("canbus.iface",_can_bus_iface);
    pt.put("canbus.proxy.host",_can_bus_proxy_host);
    pt.put("canbus.proxy.port",_can_bus_proxy_port);
    try {
        boost::property_tree::write_json(SERVER_CONFIG_FILE, pt, std::locale(), true);
    } catch( boost::property_tree::json_parser_error e) {
        LOG(ERROR) << "Can not save config file" << SERVER_CONFIG_FILE;
        return false;
    }
    return true;
}

Settings &Settings::Instance() {
    static Settings s;
    return s;
}

int Settings::web_server_port() {
    return _web_port;
}

std::string Settings::web_path() {
    return _web_path;
}

std::string Settings::can_bus_iface() {
    return _can_bus_iface;
}

std::string Settings::can_bus_proxy_host() {
    return _can_bus_proxy_host;
}

int Settings::can_bus_proxy_port() {
    return _can_bus_proxy_port;
}

int Settings::can_bus_speed() {
    return _can_bus_speed;
}
