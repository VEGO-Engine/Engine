#include "Components.h"

class HealthComponent : public Component {

public:

    HealthComponent(int health, Manager* manager, bool player) : health(health), manager(manager), player(player) {}

    ~HealthComponent() {}

    void getDamage() {
        this->health--;
    }

    int getHealth() {
        return this->health;
    }

    void init() override
    {
        createAllHearts();
    }

    void update() override {

    }

    void createAllHearts() {
        int x;

        if(player) {
            x = 10;
        } else {
            x = 750;
        }

        for(int i = 0; i < health; i++) {
            if(player) {
                createHeartComponents(x);
                x += 50;
                continue;
            }

            createHeartComponents(x);
            x -= 50;
        }
    }

    void createHeartComponents(int x) {

        auto& heart(manager->addEntity());
        heart.addComponent<TransformComponent>(x,5,1);
        heart.addComponent<SpriteComponent>("assets/chicken_neutral_knight.png");
        heart.addGroup(Game::HEARTS);
    }


private:

    int health;

    TransformComponent* transformComponent;

    Manager* manager;

    bool player; //true if player1 / false if player2

};