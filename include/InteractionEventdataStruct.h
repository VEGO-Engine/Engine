#pragma once

#include "Entity.h"
#include "InteractionListener.h"
#include "Vector2D.h"
#include <cstdint>
#include <memory>

struct InteractionEventdataStruct {
    void* actor; // suggestion, can also be used for other arbitrary data
    void* data;
    std::weak_ptr<InteractionListener> target = std::weak_ptr<InteractionListener>();
    std::shared_ptr<Vector2D> targetingReference; // required without explicit target
    uint8_t strategy = 0; // required without explicit target, defaults to none
};