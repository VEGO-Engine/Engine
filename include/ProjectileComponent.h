#pragma once

#include "Component.h"
#include "Vector2D.h"

class TransformComponent;

class ProjectileComponent : public Component
{
    //can maybe be split in separate .cpp file

public:
    ProjectileComponent(int range, int speed, Vector2D velocity, bool source) : range(range), speed(speed), velocity(velocity), source(source) {}
    ~ProjectileComponent() {}

    void init() override;
    void update() override;

    bool getSource() { return this->source; }

private:
    TransformComponent* transformComponent;

    int range = 0;
    int speed = 0;
    int distance = 0;

    const bool source; //true if from player1 / false if from player2

    Vector2D velocity;
};