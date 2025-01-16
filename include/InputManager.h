#pragma once

#include <SDL3/SDL.h>
#include <map>
#include <string>
#include <functional>
#include <vector>

class InputManager {
public:
    InputManager();
    ~InputManager();

    void init();
    void processEvents();
    void registerAction(const std::string& actionName, std::function<void()> callback);

private:
    std::map<std::string, std::vector<SDL_EventType>> actionBindings;
    std::map<std::string, std::function<void()>> actionCallbacks;
    void handleEvent(const SDL_Event& event);
};