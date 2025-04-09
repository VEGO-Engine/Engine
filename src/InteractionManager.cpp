#include "InteractionManager.h"

#include "InteractionEventdataStruct.h"
#include "InteractionListener.h"
#include "SDL3/SDL_init.h"
#include "VEGO_Event.h"
#include "Vector2D.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <ranges>
#include <type_traits>
#include <vector>

InteractionManager::InteractionManager()
{
    this->targetingFuncs.fill(nullptr);
    this->targetingFuncs.at(static_cast<std::underlying_type<InteractionManager::TargetingStrategy>::type>(InteractionManager::TargetingStrategy::closest)) = [](Vector2D* reference, std::vector<std::shared_ptr<InteractionListener>> input) {
        return std::shared_ptr<InteractionListener>();
    };
    this->targetingFuncs.at(static_cast<std::underlying_type<InteractionManager::TargetingStrategy>::type>(InteractionManager::TargetingStrategy::closest)) = [](Vector2D* reference, std::vector<std::shared_ptr<InteractionListener>> input) {
        auto min = std::ranges::min_element(input, [&reference](std::shared_ptr<InteractionListener>& a, std::shared_ptr<InteractionListener>& b) {
            std::shared_ptr<Vector2D> coordA = a->getPosition();
            std::shared_ptr<Vector2D> coordB = b->getPosition();

            if (coordB == nullptr) return true;
            if (coordA == nullptr) return false;

            return std::sqrt(std::pow(coordA->x - reference->x, 2) + std::pow(coordA->y - reference->y, 2)) < std::sqrt(std::pow(coordB->x - reference->x, 2) + std::pow(coordB->y - reference->y, 2));
        });
        return min == std::ranges::end(input) ? nullptr : *min;
    };
    this->targetingFuncs.at(static_cast<std::underlying_type<InteractionManager::TargetingStrategy>::type>(InteractionManager::TargetingStrategy::manhattenDistance)) = [](Vector2D* reference, std::vector<std::shared_ptr<InteractionListener>> input) {
        auto min = std::ranges::min_element(input, [&reference](std::shared_ptr<InteractionListener>& a, std::shared_ptr<InteractionListener>& b) {
            std::shared_ptr<Vector2D> coordA = a->getPosition();
            std::shared_ptr<Vector2D> coordB = b->getPosition();

            if (coordB == nullptr) return true;
            if (coordA == nullptr) return false;

            return (std::abs(coordA->x - reference->x) + std::abs(coordA->y - reference->y)) < (std::abs(coordB->x - reference->x) + std::abs(coordB->y - reference->y));
        });
        return min == std::ranges::end(input) ? nullptr : *min;
    };
}

SDL_AppResult InteractionManager::handleInteract(SDL_EventType type, SDL_Event* const event)
{
    if (type != vego::VEGO_Event_Interaction) { // error handling
        return SDL_APP_CONTINUE;
    }

    InteractionEventdataStruct* data = static_cast<InteractionEventdataStruct*>(event->user.data1);

    std::shared_ptr<InteractionListener> listener = data->target.lock();

    if (data->strategy != static_cast<std::underlying_type<InteractionManager::TargetingStrategy>::type>(InteractionManager::TargetingStrategy::none)) {
        listener = this->targetingFuncs.at(data->strategy)(
                data->targetingReference.get(),
                this->listeners
                    | std::views::transform(&std::weak_ptr<InteractionListener>::lock)
                    | std::views::filter(&std::shared_ptr<InteractionListener>::operator bool)
                    | std::ranges::to<std::vector>()
            );
    }

    if (listener) {
        listener->interact(data->actor, data->data);
    }

    return SDL_APP_CONTINUE;
}

void InteractionManager::registerListener(std::weak_ptr<InteractionListener> listener)
{
    this->listeners.emplace_back(listener);
}

uint8_t InteractionManager::registerTargetingFunc(TargetingFunc func)
{
    auto it = std::ranges::find_if(this->targetingFuncs, [](const auto& func) {
        return !func;
    });
    (*it) = func;
    return std::distance(this->targetingFuncs.begin(), it);
}