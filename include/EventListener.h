#pragma once

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>

class EventListener {
public:
    virtual SDL_AppResult handleEvent(SDL_EventType type, SDL_Event* event) = 0;
    EventListener() {};
    virtual ~EventListener() {};
};