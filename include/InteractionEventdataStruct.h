#pragma once

#include "Entity.h"
#include "InteractionListener.h"
#include "InteractionManager.h"
#include "Vector2D.h"
#include <cstdint>
#include <memory>

/**
 * @brief Struct to hold data for interaction events.
 * This struct is used to pass data to the interaction manager when an interaction event is triggered.
 */
struct InteractionEventdataStruct {
    /// Arbitray data to pass to the interaction listener. Can for example be an Entity ptr to represent the actor.
    void* actor;
    /// The data to pass to the interaction listener. Can be any type of pointer.
    void* data;
    /// The target of the interaction, e.g. InteractionComponent of an Entity. Is required if strategy is set to 0 (none)
    std::weak_ptr<InteractionListener> target = std::weak_ptr<InteractionListener>();
    /// Coordinates from which to base targeting on. Is required if strategy is not set to 0 (none)
    std::shared_ptr<Vector2D> targetingReference = nullptr;
    /// required without explicit target, defaults to none
    /// @sa InteractionManager::TargetingStrategy
    uint8_t strategy = 0; // int since enum would be impossibling user defined targetingStrategies

    void triggerEvent();
};