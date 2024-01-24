#include "HealthComponent.h"

#include "Components.h"

void HealthComponent::init() 
{
    createAllHearts();
}

void HealthComponent::createAllHearts()
{
    int x; //starting position for first health icon

    if(player) {
        x = 10;
    } else {
        x = 730;
    }

    for(int i = 0; i < health; i++) {

        //checks for player side
        if(player) {
            createHeartComponents(x);
            x += 50;
            continue;
        }

        createHeartComponents(x);
        x -= 50;
    }
}

    void HealthComponent::createHeartComponents(int x) 
{
    auto& heart(manager->addEntity());
    heart.addComponent<TransformComponent>(x,5,2);
    heart.addComponent<SpriteComponent>("assets/heart.png");
    heart.addGroup((size_t)GroupLabel::HEARTS);
}