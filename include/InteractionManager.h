#pragma once

#include "InteractionListener.h"

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>
#include <ranges>

// TODO: ranges concept to avoid to<vector> in cpp
typedef std::function<std::shared_ptr<InteractionListener>(Vector2D*, std::vector<std::shared_ptr<InteractionListener>>)> TargetingFunc;

class InteractionManager {
public:
    InteractionManager();
    InteractionManager (const InteractionManager&) = delete;
    InteractionManager& operator= (const InteractionManager&) = delete;

    enum class TargetingStrategy : uint8_t {
        none = 0,
        closest,
        manhattenDistance
    };

    SDL_AppResult handleInteract(SDL_EventType type, SDL_Event* const event);
    void registerListener(std::weak_ptr<InteractionListener> listener);
    uint8_t registerTargetingFunc(TargetingFunc func);
private:

    std::vector<std::weak_ptr<InteractionListener>> listeners;
    std::array<TargetingFunc, 256> targetingFuncs;
};