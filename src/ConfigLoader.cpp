#include "ConfigLoader.h"

#include <fstream>

ConfigLoader::ConfigLoader() {
    baseConfig = loadConfigFromJSON("config.json");
}

ConfigLoader::~ConfigLoader() {}

void ConfigLoader::init() {
    if (!customConfig.has_value()) {
        finalConfig = baseConfig;
        return;
    }
    finalConfig = mergeConfigs(baseConfig, customConfig.value());
}

json ConfigLoader::loadConfigFromJSON(const std::string& path) {
    std::ifstream config_file(path);
    json config;

    if (!config_file.is_open()) {
        throw std::runtime_error(std::string("Could not load config file at: " + path));
    }

    config_file >> config;
    return config;
}


void ConfigLoader::setCustomConfig(const std::optional<std::string>& path) {
    customConfig = path;
}

json ConfigLoader::mergeConfigs(json baseConfig, json customConfig) {
    for (auto& entry : customConfig.items()) {
        baseConfig[entry.key()] = entry.value();
    }
    return baseConfig;
}

json ConfigLoader::getFinalConfig() {
    return finalConfig;
}



