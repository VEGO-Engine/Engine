#pragma once

#include "EventListener.h"

#include <initializer_list>
#include <map>
#include <vector>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"

class EventManager {
public:
    void registerListener(EventListener* listener, std::initializer_list<SDL_EventType> eventTypes);
    SDL_AppResult handleEvent(SDL_Event* const event);
private:
    std::map<SDL_EventType, std::vector<EventListener*>> eventListeners = std::map<SDL_EventType, std::vector<EventListener*>>();
};