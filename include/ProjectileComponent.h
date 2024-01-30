#pragma once

#include "Component.h"
#include "Vector2D.h"
#include "Constants.h"

class TransformComponent;

class ProjectileComponent : public Component
{
    //can maybe be split in separate .cpp file

public:
    ProjectileComponent(int range, int speed, Vector2D direction) : range(range), speed(speed), direction(direction) {}
    ~ProjectileComponent() {}

    void init() override;
    void update() override;

private:
    TransformComponent* transformComponent;

    int range = 0;
    int speed = 0;
    int distance = 0;

    Vector2D direction;
};