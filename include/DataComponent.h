#pragma once

#include <map>
#include <any>
#include <string>
#include <optional>
#include "Component.h"

class DataComponent : public Component
{
public:
    DataComponent() {};
    ~DataComponent() {};
    template <typename T>
    void setEntry(const std::string& key, const T& value) { dataMap.insert_or_assign(key, value); }

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