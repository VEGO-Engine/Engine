#include "EventManager.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_stdinc.h"
#include "VEGO_Event.h"
#include <algorithm>
#include <functional>
#include <ranges>
#include <vector>

Uint32 vego::VEGO_Event_Interaction;

EventManager::EventManager()
{
    /// \TODO: from c++26 you (should be able to) can get the amount of name values in an enum
    vego::VEGO_Event_Interaction = SDL_RegisterEvents(1); // TODO: error handling
}


void EventManager::registerListener(EventListener listener, std::initializer_list<Uint32> eventTypes)
{
    std::ranges::for_each(eventTypes.begin(), eventTypes.end(), [this, &listener](const Uint32& eventType) {
        if (!this->eventListeners.contains(eventType)) {
            this->eventListeners.insert({eventType, std::vector<EventListener>()});
        }
        this->eventListeners.at(eventType).emplace_back(listener);
    });
}

SDL_AppResult EventManager::handleEvent(SDL_Event* event)
{
    SDL_EventType type = (SDL_EventType) event->type;
    if (this->eventListeners.contains(type)) {
        std::vector<SDL_AppResult> results;
        for (auto& listener : this->eventListeners.at(type)) {
            results.emplace_back(listener((SDL_EventType) event->type, event));
        }
        if (std::ranges::contains(results, SDL_APP_FAILURE))
            return SDL_APP_FAILURE;
        if (std::ranges::contains(results, SDL_APP_SUCCESS))
            return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}