#pragma once

#include <SDL.h>
#include <map>

#include "Component.h"
#include "Key.h"

class InputComponent : public Component
{
public:
    InputComponent();
    ~InputComponent();

    void init() override;
	void update() override;

    bool isKeyDown(Key key);

	std::string componentName() override { return "InputComponent"; }

private:
    const Uint8* m_keyStates;
    SDL_Scancode mapKeyToSDL(Key key);
    std::map<Key, SDL_Scancode> m_keyMappings;
    void InitKeyMappings();
};
