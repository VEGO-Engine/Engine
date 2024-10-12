#pragma once

#include "Component.h"
#include <string>

class PlayerComponent : public Component
{
public:

	std::string componentName() override { return "PlayerComponent"; }
private:
};