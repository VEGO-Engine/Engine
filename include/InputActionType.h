#pragma once

#include <variant>

using InputValue = std::variant<bool, float>;

enum class InputActionType
{
    Boolean,
    Float
};