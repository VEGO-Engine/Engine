#include "InputManager.h"
#include <iostream>

InputManager::InputManager() {}

InputManager::~InputManager() {
    SDL_Quit();
}

void InputManager::init() {
    if (SDL_Init(SDL_INIT_EVENTS) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return;
    }
}

void InputManager::processEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        handleEvent(event);
    }
}

void InputManager::registerAction(const std::string& actionName, std::function<void()> callback) {
    actionCallbacks[actionName] = callback;
}

void InputManager::handleEvent(const SDL_Event& event) {
    for (const auto& [actionName, bindings] : actionBindings) {
        for (const auto& binding : bindings) {
            if (event.type == binding) {
                if (actionCallbacks.find(actionName) != actionCallbacks.end()) {
                    actionCallbacks[actionName]();
                }
            }
        }
    }
}