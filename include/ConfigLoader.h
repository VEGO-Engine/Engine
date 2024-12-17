#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ConfigLoader {

public:
    ConfigLoader();
    ~ConfigLoader();

    void init();

    void setCustomConfig(const std::optional<std::string>& path);

    json getFinalConfig();

private:

    std::optional<std::string> customConfigPath;
    json finalConfig;

    json loadConfigFromJSON(const std::string& path);
    json mergeConfigs(json baseConfig, json customConfig); //<! Merges 2 config.json files, prioritising the custom to the base one
};
