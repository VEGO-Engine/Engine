#include "HealthComponent.h"

#include "Components.h"
#include "Direction.h"
#include "Entity.h"
#include "Game.h"
#include <cstdio>

void HealthComponent::init() 
{
    refreshHearts();
}

void HealthComponent::modifyHealth(int health) 
{
    this->health += health;
    this->refreshHearts();
}

void HealthComponent::refreshHearts()
{
    // clear hearts if exist
    for (auto& heart : this->entity->getManager().getGroup((size_t) GroupLabel::HEARTS)) {
        if (heart->getTeam() == this->entity->getTeam()) {
            heart->destroy();
        }
    }

    int x; //starting position for first health icon

    if(side == Direction::LEFT) {
        x = 10;
    } else {
        x = 730;
    }

    for(int i = 0; i < health; i++) {
        
        //checks for player side
        if (side == Direction::LEFT) {
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
    auto& heart(this->entity->getManager().addEntity());
    heart.addComponent<TransformComponent>(x,5,2);
    heart.addComponent<SpriteComponent>("assets/heart.png");
    heart.addGroup((size_t)GroupLabel::HEARTS);
    heart.setTeam(this->entity->getTeam());
}