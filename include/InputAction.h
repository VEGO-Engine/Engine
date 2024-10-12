#pragma once

#include <functional>
#include <vector>
#include <string>

#include "Key.h"
#include "InputActionType.h"

struct InputAction
{
    std::string name;
    std::vector<Key> keys;
    std::function<void()> callback;
    InputActionType type;
    InputValue value;

    InputAction() = default;
    InputAction(const std::string& actionName, std::function<void()> actionCallback)
        : name(actionName), callback(actionCallback) {}

    InputAction(const std::string& actionName, std::function<void()> actionCallback, InputActionType actionType)
        : name(actionName), callback(actionCallback), type(actionType)
    {
        switch (type)
        {
            case InputActionType::Boolean:
                value = false;
                break;

            case InputActionType::Float:
                value = 0.0f;
                break;

            default:
                value = false;
                break;
        }   
    }
};