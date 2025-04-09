#pragma once

#include "Component.h"
#include "Vector2D.h"
#include "Constants.h"
#include "SoundEffects.h"

class TransformComponent;

class ProjectileComponent : public Component
{
    //can maybe be split in separate .cpp file

public:
    ProjectileComponent(int range, int speed, Vector2D direction, Entity* owner, SoundEffects soundEffect)
    : range(range), speed(speed), direction(direction), owner(owner), soundEffect(soundEffect) {}
    ~ProjectileComponent() {}

    void init() override;
    void update(uint_fast16_t diffTime) override;

private:
    TransformComponent* transformComponent;

    int range = 0;
    float speed = 0;
    float distance = 0;

    Entity* owner = nullptr;

    Vector2D direction;

    SoundEffects soundEffect;
};