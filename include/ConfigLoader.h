#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ConfigLoader {

public:
    ConfigLoader();
    ~ConfigLoader();

    void init();

    void setCustomConfig(std::string path);

private:
    json baseConfig;
    std::optional<json> customConfig;
    json finalConfig;

    json loadConfigFromJSON(const std::string& path);
    json mergeConfigs(json baseConfig, json customConfig); //<! Merges 2 config.json files, prioritising the custom to the base one
};
