#include "InputManager.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, InputManager::Key key) {
    static const std::unordered_map<InputManager::Key, std::string> keyToString {
        {InputManager::Key::UP, "UP"},
        {InputManager::Key::DOWN, "DOWN"},
        {InputManager::Key::LEFT, "LEFT"},
        {InputManager::Key::RIGHT, "RIGHT"},
        {InputManager::Key::SPACE, "SPACE"},
        {InputManager::Key::ENTER, "ENTER"},
        {InputManager::Key::ESCAPE, "ESCAPE"},
        {InputManager::Key::TAB, "TAB"},
        {InputManager::Key::BACKSPACE, "BACKSPACE"},
        {InputManager::Key::DELETE, "DELETE"},
        {InputManager::Key::HOME, "HOME"},
        {InputManager::Key::END, "END"},
        {InputManager::Key::PAGE_UP, "PAGE_UP"},
        {InputManager::Key::PAGE_DOWN, "PAGE_DOWN"},
        {InputManager::Key::INSERT, "INSERT"},
        {InputManager::Key::CAPS_LOCK, "CAPS_LOCK"},
        {InputManager::Key::LEFT_SHIFT, "LEFT_SHIFT"},
        {InputManager::Key::RIGHT_SHIFT, "RIGHT_SHIFT"},
        {InputManager::Key::LEFT_CTRL, "LEFT_CTRL"},
        {InputManager::Key::RIGHT_CTRL, "RIGHT_CTRL"},
        {InputManager::Key::LEFT_ALT, "LEFT_ALT"},
        {InputManager::Key::RIGHT_ALT, "RIGHT_ALT"},
        {InputManager::Key::F1, "F1"},
        {InputManager::Key::F2, "F2"},
        {InputManager::Key::F3, "F3"},
        {InputManager::Key::F4, "F4"},
        {InputManager::Key::F5, "F5"},
        {InputManager::Key::F6, "F6"},
        {InputManager::Key::F7, "F7"},
        {InputManager::Key::F8, "F8"},
        {InputManager::Key::F9, "F9"},
        {InputManager::Key::F10, "F10"},
        {InputManager::Key::F11, "F11"},
        {InputManager::Key::F12, "F12"},
        {InputManager::Key::A, "A"},
        {InputManager::Key::B, "B"},
        {InputManager::Key::C, "C"},
        {InputManager::Key::D, "D"},
        {InputManager::Key::E, "E"},
        {InputManager::Key::F, "F"},
        {InputManager::Key::G, "G"},
        {InputManager::Key::H, "H"},
        {InputManager::Key::I, "I"},
        {InputManager::Key::J, "J"},
        {InputManager::Key::K, "K"},
        {InputManager::Key::L, "L"},
        {InputManager::Key::M, "M"},
        {InputManager::Key::N, "N"},
        {InputManager::Key::O, "O"},
        {InputManager::Key::P, "P"},
        {InputManager::Key::Q, "Q"},
        {InputManager::Key::R, "R"},
        {InputManager::Key::S, "S"},
        {InputManager::Key::T, "T"},
        {InputManager::Key::U, "U"},
        {InputManager::Key::V, "V"},
        {InputManager::Key::W, "W"},
        {InputManager::Key::X, "X"},
        {InputManager::Key::Y, "Y"},
        {InputManager::Key::Z, "Z"},
        {InputManager::Key::NUM_0, "NUM_0"},
        {InputManager::Key::NUM_1, "NUM_1"},
        {InputManager::Key::NUM_2, "NUM_2"},
        {InputManager::Key::NUM_3, "NUM_3"},
        {InputManager::Key::NUM_4, "NUM_4"},
        {InputManager::Key::NUM_5, "NUM_5"},
        {InputManager::Key::NUM_6, "NUM_6"},
        {InputManager::Key::NUM_7, "NUM_7"},
        {InputManager::Key::NUM_8, "NUM_8"},
        {InputManager::Key::NUM_9, "NUM_9"},
        {InputManager::Key::LEFT_BRACKET, "LEFT_BRACKET"},
        {InputManager::Key::RIGHT_BRACKET, "RIGHT_BRACKET"},
        {InputManager::Key::SEMICOLON, "SEMICOLON"},
        {InputManager::Key::APOSTROPHE, "APOSTROPHE"},
        {InputManager::Key::COMMA, "COMMA"},
        {InputManager::Key::PERIOD, "PERIOD"},
        {InputManager::Key::SLASH, "SLASH"},
        {InputManager::Key::BACKSLASH, "BACKSLASH"},
        {InputManager::Key::GRAVE, "GRAVE"}
    };

    auto it = keyToString.find(key);
    if (it != keyToString.end()) {
        os << it->second;
    } else {
        os << "UNKNOWN_KEY";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const InputManager::InputAction& action) {
    os << action.name << " with binding(s): ";
    for (size_t i = 0; i < action.bindings.size(); ++i) {
        os << action.bindings[i];

        if (i < action.bindings.size() - 1) {
            os << ", ";
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const InputManager::InputAction* action) {
    if (action) {
        os << *action;
    } else {
        os << "NULL_ACTION";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<InputManager::InputAction>& actions) {
    os << "Actions: ";
    if (actions.empty()) {
        os << "None";
    } else {
        for (size_t i = 0; i < actions.size(); ++i) {
            os << actions[i];
            if (i < actions.size() - 1) {
                os << " | ";
            }
        }
    }
    return os;
}

// TODO: find out why it doesnt work??
std::ostream& operator<<(std::ostream& os, const std::vector<InputManager::InputAction*>& actions) {
    os << "Actions: ";
    if (actions.empty()) {
        os << "None";
    } else {
        for (size_t i = 0; i < actions.size(); ++i) {
            if (actions[i]) {
                os << *actions[i];
            } else {
                os << "NULL_ACTION";
            }
            if (i < actions.size() - 1) {
                os << " | ";
            }
        }
    }
    return os;
}




// overloads end --------------------------------------------------------------------------------------





InputManager::InputManager() : activeContext("Default") {}

void InputManager::init() {
    if (SDL_Init(SDL_INIT_EVENTS) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }
}

void InputManager::initKeyMap() {
    keyMap = {
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

void InputManager::registerAction(const std::string& actionName, const std::vector<Key>& keys, std::function<void()> callback, const std::string& context) {
    actionsByContext[context].emplace_back(actionName, keys, callback);
    InputAction& storedAction = actionsByContext[context].back();
    for (const auto& key : keys) {
        actionsByKey[key].push_back(&storedAction);
    }
    std::cout << "Registered action: " << storedAction << " in context: " << context << std::endl;
}

void InputManager::rebindAction(const std::string& actionName, const std::vector<Key>& newBindings, const std::string& context) {
    auto it = actionsByContext.find(context);
    if (it != actionsByContext.end()) {
        for (auto& action : it->second) {
            if (action.name == actionName) {
                for (const auto& key : action.bindings) {
                    auto& keyActions = actionsByKey[key];
                    keyActions.erase(std::remove(keyActions.begin(), keyActions.end(), &action), keyActions.end());
                    if (keyActions.empty()) {
                        actionsByKey.erase(key);
                    }
                }

                action.bindings = newBindings;

                for (const auto& key : newBindings) {
                    actionsByKey[key].push_back(&action);
                }

                std::cout << "Rebound action: " << actionName << " in context: " << context << " to new bindings: ";
                for (const auto& key : newBindings) {
                    std::cout << key << " ";
                }
                std::cout << std::endl;
                return;
            }
        }
    }
    std::cout << "Action not found: " << actionName << " in context: " << context << std::endl;
}

void InputManager::removeBindings(const std::string& actionName, const std::string& context) {
    auto it = actionsByContext.find(context);
    if (it != actionsByContext.end()) {
        for (auto& action : it->second) {
            if (action.name == actionName) {
                action.bindings.clear();
                std::cout << "Removed bindings for action: " << actionName << " in context: " << context << std::endl;
                return;
            }
        }
    }
    std::cout << "Action not found: " << actionName << " in context: " << context << std::endl;
}

std::vector<InputManager::Key> InputManager::getBindings(const std::string& actionName, const std::string& context) const {
    auto it = actionsByContext.find(context);
    if (it != actionsByContext.end()) {
        for (const auto& action : it->second) {
            if (action.name == actionName) {
                return action.bindings;
            }
        }
    }
    std::cout << "Action not found: " << actionName << " in context: " << context << "\n";
    return {};
}

std::vector<InputManager::InputAction*> InputManager::getActionsByKey(const Key key) const {
    auto it = actionsByKey.find(key);
    if (it != actionsByKey.end()) {
        std::cout << "DEBUG: Found " << it->second.size() << " actions for key " << key << std::endl;
        return it->second;
    }
    std::cout << "DEBUG: No actions found for key " << key << std::endl;
    return {};
}

void InputManager::setActiveContext(const std::string& context) {
    activeContext = context;
    std::cout << "Active context set to: " << activeContext << std::endl;
}

std::string InputManager::getActiveContext() const {
    return activeContext;
}

void InputManager::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        std::cout << "Event detected: " << event.type << std::endl;
        handleEvent(event);
    }
}

void InputManager::handleEvent(const SDL_Event& event) {
    if (event.type != SDL_EVENT_KEY_DOWN) return; // TODO: add other events if necessary // TODO: Controller how??
    std::cout << "in handleEvent" << std::endl;

    auto keyIt = std::ranges::find_if(keyMap,
    [&](const auto& pair) { return pair.second == event.key.scancode; });

    if (keyIt != keyMap.end()) {
        std::cout << "in != keymap.end" << std::endl;

        Key pressedKey = keyIt->first;
        auto actionIt = actionsByKey.find(pressedKey);
        if (actionIt != actionsByKey.end()) {
            std::cout << "in != actionsByKey.end" << std::endl;

            for (auto* action : actionIt->second) {
                std::cout << "before if(action)" << std::endl;
                if (action) {
                    std::cout << "after if(action)" << std::endl;

                    auto& activeActions = actionsByContext[activeContext];
                    if (std::ranges::find_if(activeActions,
                    [&](const InputAction& act) { return &act == action; }) != activeActions.end()) {
                        std::cout << "Action triggered: " << action->name << " in context: " << activeContext << std::endl;
                        action->callback();
                    }
                }
            }
        }
    }
}