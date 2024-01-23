#pragma once

#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"

class ProjectileComponent : public Component {

    //can maybe be split in separate .cpp file

public:

    ProjectileComponent(int range, int speed, Vector2D velocity, bool source) : range(range), speed(speed), velocity(velocity), source(source) {

    }

    ~ProjectileComponent() {}

    void init() override {
        transformComponent = &entity->getComponent<TransformComponent>();
    }

    void update() override {

        transformComponent->velocity = velocity;

        distance += speed;

        if (distance > range) {
            entity->destroy();
            entity->getComponent<ColliderComponent>().removeCollision();
            //std::cout << "out of range" << std::endl;
        }

    }

    bool getSource() {
        return this->source;
    }


private:

    TransformComponent* transformComponent;

    int range = 0;
    int speed = 0;
    int distance = 0;

    const bool source; //true if from player1 / false if from player2

    Vector2D velocity;
};