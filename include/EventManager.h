#pragma once

#include <functional>
#include <initializer_list>
#include <map>
#include <vector>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"

typedef std::function<SDL_AppResult(SDL_EventType, SDL_Event* const)> EventListener;

class EventManager {
public:
    EventManager();

    void registerListener(EventListener listener, std::initializer_list<Uint32> eventTypes);
    SDL_AppResult handleEvent(SDL_Event* const event);
private:
    std::map<Uint32, std::vector<EventListener>> eventListeners = std::map<Uint32, std::vector<EventListener>>();
};