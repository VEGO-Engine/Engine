#pragma once

#include <map>
#include <any>
#include <string>
#include <optional>
#include "Component.h"

//! \brief DataComponent class to centrally store data about an entity such as stats
class DataComponent : public Component
{
public:
    DataComponent() {};
    ~DataComponent() {};
    /**
     * @brief Set a key-value pair of any type in the data map
     * @details e.g. \code{.cpp}setEntry("speed", 180);\endcode in this case the key is "speed" and the value is set to an integer of 180
     * @param key The name to store the value under
     * @param value The value to store of type T
     */
    template <typename T>
    void setEntry(const std::string& key, const T& value) { dataMap.insert_or_assign(key, value); }

    /**
     * @brief Get a value of type T from the data map
     * @details e.g. \code{.cpp}getEntry<int>("speed");\endcode in this case the key is "speed" and the value is returned as an integer
     * @param key The name to retrieve the value from
     * @return An optional of type T containing the value if it exists and matches in typeid, otherwise std::nullopt
     */
    template<typename T>
    std::optional<T> getEntry(std::string key) const {
        if (!this->dataMap.contains(key)) return std::nullopt;
        const std::any& value = this->dataMap.at(key);
        if (value.type() != typeid(T)) { return std::nullopt; }
        return std::any_cast<T>(value);
    }
private:
    std::map<std::string, std::any> dataMap;
};