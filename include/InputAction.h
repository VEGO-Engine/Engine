#pragma once

#include <functional>
#include <vector>
#include <string>
#include "Key.h"

struct InputAction
{
    std::string name;
    std::vector<Key> keys;
    std::function<void()> callback;

    InputAction() = default;
    InputAction(const std::string& actionName, std::function<void()> actionCallback)
        : name(actionName), callback(actionCallback) {}

};