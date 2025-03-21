#include "EventManager.h"
#include "EventListener.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include <algorithm>
#include <ranges>
#include <vector>

void EventManager::registerListener(EventListener* listener, std::initializer_list<SDL_EventType> eventTypes)
{
    std::ranges::for_each(eventTypes.begin(), eventTypes.end(), [this, &listener](const SDL_EventType& eventType) {
        if (!this->eventListeners.contains(eventType)) {
            this->eventListeners.insert({eventType, std::vector<EventListener*>()});
        }
        this->eventListeners.at(eventType).emplace_back(listener);
    });
}

SDL_AppResult EventManager::handleEvent(SDL_Event* event)
{
    SDL_EventType type = (SDL_EventType) event->type;
    if (this->eventListeners.contains(type)) {
        auto results = this->eventListeners.at(type) | std::views::transform(
            [&event](EventListener* listener) {
                return listener->handleEvent((SDL_EventType) event->type, event);
            });
        if (std::ranges::contains(results, SDL_APP_FAILURE))
            return SDL_APP_FAILURE;
        if (std::ranges::contains(results, SDL_APP_SUCCESS))
            return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}