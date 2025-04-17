#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL.h>
#include <map>
#include <string>
#include <functional>
#include <vector>
#include <iostream>

//! \brief InputManager class to handle input events and actions
//! \details This class manages input events, allowing for the registration of actions and their corresponding key bindings.
class InputManager {
public:
//! \brief A list of every key that can be bound to an action
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

//! \brief InputAction struct to represent an action and its bindings
//! \param name The name of the action
//! \param bindings The keys that are bound to this action
//! \param callback The function to call when the action is triggered
    struct InputAction {
        std::string name;
        std::vector<Key> bindings;
        std::function<void(bool)> callback;
    };

    InputManager();
    ~InputManager();

    void init(); // see if necessary
    void processEvents();
    //! \brief Register an action with a name, key bindings, and a callback function
    //! \param actionName The name of the action
    //! \param keys The keys that are bound to this action
    //! \param callback The function to call when the action is triggered
    //! \param context The context in which the action is valid can be used to switch between e.g. gameplay and menu so the same keys can be used for different actions
    void registerAction(const std::string& actionName, const std::vector<Key>& keys, std::function<void(bool)> callback, const std::string& context = "Default");

    //! \brief set the active context, is "Default" by default
    //! \param context The name of the context to set as active
    void setActiveContext(const std::string& context);

    //! \brief Get the active context
    std::string getActiveContext() const;

    //void rebindAction(const std::string& actionName, const std::vector<Key>& newBindings, const std::string& context);
    //void removeBindings(const std::string& actionName, const std::string& context);
    //std::vector<Key> getBindings(const std::string& actionName, const std::string& context) const;
    std::vector<InputAction*> getActionsByKey(const Key key) const;

    SDL_AppResult handleEvent(SDL_EventType type, SDL_Event* const event);

    void initKeyMap();
private:
    // TODO: flesh this out to avoid loops in process actions
    // additionally to actionsByContext, not instead
    std::map<std::string, std::map<Key, std::vector<InputAction*>>> actionsByContextAndKey;

    std::map<Key, SDL_Scancode> keyMap;
    std::string activeContext;
};

std::ostream& operator<<(std::ostream& os, InputManager::Key key);
std::ostream& operator<<(std::ostream& os, const InputManager::InputAction& action);
std::ostream& operator<<(std::ostream& os, const InputManager::InputAction* action);
std::ostream& operator<<(std::ostream& os, const std::vector<InputManager::InputAction>& actions);
std::ostream& operator<<(std::ostream& os, const std::vector<InputManager::InputAction*>& actions);
