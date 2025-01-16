#pragma once

#include <SDL3/SDL.h>
#include <map>
#include <string>
#include <functional>
#include <vector>

class InputManager {
public:
    enum class EventType {
        KeyDown,
        KeyUp
    };

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

    struct InputAction {
        std::string name;
        std::vector<Key> bindings;
        std::function<void()> callback;
        std::string context;
    };

    InputManager();
    ~InputManager();

    void init(); // see if necessary
    void processEvents();
    void registerAction(const std::string& actionName, const std::vector<Key>& keys, std::function<void()> callback, const std::string& context);

    void setActiveContext(const std::string& context);
    std::string getActiveContext() const;

private:
    std::map<std::string, std::vector<InputAction>> actionsByContext;
    std::map<Key, SDL_Scancode> keyMap;
    std::string activeContext;

    void initKeyMap();
    void handleEvent(const SDL_Event& event);
};