#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

/*!
 * \class ConfigLoader
 * \brief Enables configuration of specific engine variables via a custom JSON file.
 *
 *  The Config loader is responsible to handling customization for engine parameters like the
 *  window icon, window title, ... through json files.
 *
 *  It includes a standard config file and the option to add a custom one by overwriting the setConfigFilePath()
 *  function within the implementation of the \ref Game class. Those files get merged, with a priorization on
 *  the parameters set within the custom config file.
 *
 *
 *  The currently available config parameters with their default values are:
 *  \include ../config.json
 *
 */

class ConfigLoader {

public:
    ConfigLoader();
    ~ConfigLoader();

    /*!
     *  \brief Creates the final config for the engine
     *
     *  Loads the default config and then creates the final config by either merging
     *  (if the custom config has been set) or by implementing the standard config (if no custom
     *  config was set).
     *
     *  \private
     */
    void init();
    /*!
     * \brief Sets the customConfigPath variable
     *
     * \param path optional variable that should include the path to the custom config JSON file
     *
     * \private
     */
    void setCustomConfig(const std::optional<std::string>& path);
    /*!
     * \brief Gets final configuration
     * \return `json` variable containing the final config
     * \private
     */
    json getFinalConfig();

private:

    std::optional<std::string> customConfigPath;
    json finalConfig;

    json loadConfigFromJSON(const std::string& path);
    json mergeConfigs(json baseConfig, json customConfig); //<! Merges 2 config.json files, prioritising the custom to the base one
};
