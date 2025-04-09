#pragma once

#include "Vector2D.h"
#include <memory>

class InteractionListener {
public:
    InteractionListener() { };
    virtual ~InteractionListener() { };

    virtual void interact(void* actor, void* data) = 0;
    virtual std::shared_ptr<Vector2D> getPosition() // required for targeting strategy, return null to only allow explicit targeting
    {
        return nullptr;
    }

};