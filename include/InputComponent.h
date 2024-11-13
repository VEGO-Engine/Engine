#pragma once
#include <SDL.h>
#include <map>

#include "Component.h"

enum class Key
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE,
    ENTER,
    ESCAPE,
    TAB,
    BACKSPACE,
    DELETE,
    HOME,
    END,
    PAGE_UP,
    PAGE_DOWN,
    INSERT,
    CAPS_LOCK,
    LEFT_SHIFT,
    RIGHT_SHIFT,
    LEFT_CTRL,
    RIGHT_CTRL,
    LEFT_ALT,
    RIGHT_ALT,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    NUM_0,
    NUM_1,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    SEMICOLON,
    APOSTROPHE,
    COMMA,
    PERIOD,
    SLASH,
    BACKSLASH,
    GRAVE
};

class InputComponent : public Component
{
public:
    InputComponent();
    ~InputComponent();

    void init() override;
	void update() override;

    bool isKeyDown(Key key);

private:
    const Uint8* m_keyStates;
    SDL_Scancode mapKeyToSDL(Key key);
    std::map<Key, SDL_Scancode> m_keyMappings;
    void InitKeyMappings();
};
