#include "InputComponent.h"

InputComponent::InputComponent()
{
    m_keyStates = SDL_GetKeyboardState(NULL);
    InitKeyMappings();
}

InputComponent::~InputComponent() = default;

void InputComponent::init()
{
    // m_keyStates = SDL_GetKeyboardState(NULL);
    // InitKeyMappings();
}

void InputComponent::update()
{
    SDL_PumpEvents();
}

bool InputComponent::isKeyDown(Key key)
{
    return m_keyStates[mapKeyToSDL(key)];
}

SDL_Scancode InputComponent::mapKeyToSDL(Key key)
{
    auto it = m_keyMappings.find(key);
    if (it == m_keyMappings.end())
    {
        return SDL_SCANCODE_UNKNOWN;
    }
    return it->second;
}

void InputComponent::InitKeyMappings()
{
    m_keyMappings =
    {
        {Key::UP, SDL_SCANCODE_UP},
        {Key::DOWN, SDL_SCANCODE_DOWN},
        {Key::LEFT, SDL_SCANCODE_LEFT},
        {Key::RIGHT, SDL_SCANCODE_RIGHT},
        {Key::SPACE, SDL_SCANCODE_SPACE},
        {Key::ENTER, SDL_SCANCODE_RETURN},
        {Key::ESCAPE, SDL_SCANCODE_ESCAPE},
        {Key::TAB, SDL_SCANCODE_TAB},
        {Key::BACKSPACE, SDL_SCANCODE_BACKSPACE},
        {Key::DELETE, SDL_SCANCODE_DELETE},
        {Key::HOME, SDL_SCANCODE_HOME},
        {Key::END, SDL_SCANCODE_END},
        {Key::PAGE_UP, SDL_SCANCODE_PAGEUP},
        {Key::PAGE_DOWN, SDL_SCANCODE_PAGEDOWN},
        {Key::INSERT, SDL_SCANCODE_INSERT},
        {Key::CAPS_LOCK, SDL_SCANCODE_CAPSLOCK},
        {Key::LEFT_SHIFT, SDL_SCANCODE_LSHIFT},
        {Key::RIGHT_SHIFT, SDL_SCANCODE_RSHIFT},
        {Key::LEFT_CTRL, SDL_SCANCODE_LCTRL},
        {Key::RIGHT_CTRL, SDL_SCANCODE_RCTRL},
        {Key::LEFT_ALT, SDL_SCANCODE_LALT},
        {Key::RIGHT_ALT, SDL_SCANCODE_RALT},
        {Key::F1, SDL_SCANCODE_F1},
        {Key::F2, SDL_SCANCODE_F2},
        {Key::F3, SDL_SCANCODE_F3},
        {Key::F4, SDL_SCANCODE_F4},
        {Key::F5, SDL_SCANCODE_F5},
        {Key::F6, SDL_SCANCODE_F6},
        {Key::F7, SDL_SCANCODE_F7},
        {Key::F8, SDL_SCANCODE_F8},
        {Key::F9, SDL_SCANCODE_F9},
        {Key::F10, SDL_SCANCODE_F10},
        {Key::F11, SDL_SCANCODE_F11},
        {Key::F12, SDL_SCANCODE_F12},
        {Key::A, SDL_SCANCODE_A},
        {Key::B, SDL_SCANCODE_B},
        {Key::C, SDL_SCANCODE_C},
        {Key::D, SDL_SCANCODE_D},
        {Key::E, SDL_SCANCODE_E},
        {Key::F, SDL_SCANCODE_F},
        {Key::G, SDL_SCANCODE_G},
        {Key::H, SDL_SCANCODE_H},
        {Key::I, SDL_SCANCODE_I},
        {Key::J, SDL_SCANCODE_J},
        {Key::K, SDL_SCANCODE_K},
        {Key::L, SDL_SCANCODE_L},
        {Key::M, SDL_SCANCODE_M},
        {Key::N, SDL_SCANCODE_N},
        {Key::O, SDL_SCANCODE_O},
        {Key::P, SDL_SCANCODE_P},
        {Key::Q, SDL_SCANCODE_Q},
        {Key::R, SDL_SCANCODE_R},
        {Key::S, SDL_SCANCODE_S},
        {Key::T, SDL_SCANCODE_T},
        {Key::U, SDL_SCANCODE_U},
        {Key::V, SDL_SCANCODE_V},
        {Key::W, SDL_SCANCODE_W},
        {Key::X, SDL_SCANCODE_X},
        {Key::Y, SDL_SCANCODE_Y},
        {Key::Z, SDL_SCANCODE_Z},
        {Key::NUM_0, SDL_SCANCODE_0},
        {Key::NUM_1, SDL_SCANCODE_1},
        {Key::NUM_2, SDL_SCANCODE_2},
        {Key::NUM_3, SDL_SCANCODE_3},
        {Key::NUM_4, SDL_SCANCODE_4},
        {Key::NUM_5, SDL_SCANCODE_5},
        {Key::NUM_6, SDL_SCANCODE_6},
        {Key::NUM_7, SDL_SCANCODE_7},
        {Key::NUM_8, SDL_SCANCODE_8},
        {Key::NUM_9, SDL_SCANCODE_9},
        {Key::LEFT_BRACKET, SDL_SCANCODE_LEFTBRACKET},
        {Key::RIGHT_BRACKET, SDL_SCANCODE_RIGHTBRACKET},
        {Key::SEMICOLON, SDL_SCANCODE_SEMICOLON},
        {Key::APOSTROPHE, SDL_SCANCODE_APOSTROPHE},
        {Key::COMMA, SDL_SCANCODE_COMMA},
        {Key::PERIOD, SDL_SCANCODE_PERIOD},
        {Key::SLASH, SDL_SCANCODE_SLASH},
        {Key::BACKSLASH, SDL_SCANCODE_BACKSLASH},
        {Key::GRAVE, SDL_SCANCODE_GRAVE}
    };
}
