#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SDL_rect.h>

#include "CollisionHandler.h"
#include "Entity.h"
#include "ColliderComponent.h"
#include "Vector2D.h"

class MockColliderComponent : public ColliderComponent {
public:
    MockColliderComponent() : ColliderComponent("") {

    };

    SDL_Rect collider;
};

class MockManager : public Manager {
    // do nothing
};

class MockEntity : public Entity {
public:
    MockEntity() : Entity(*(new MockManager())) {
        this->comp = MockColliderComponent();
    };

    MockColliderComponent comp;

    template<typename T>
    bool hasComponent() const {
        return true; // Simplified for testing
    }
    
    template<typename T>
    T& getComponent() {
        return comp;
    }
};

// Test fixture
class CollisionHandlerTest : public::testing::Test {
public:
    CollisionHandlerTest() {};
    CollisionHandler collisionHandler = CollisionHandler(*(new MockManager()));
    MockEntity entityA, entityB;
    Vector2D posModA, posModB;

    void SetUp() override {
        // Initialize entities
        //MockEntity entityA;
        //MockEntity entityB;

        // Set up colliders for testing
        entityA.comp.collider = {0, 0, 10, 10};
        entityB.comp.collider = {15, 15, 10, 10};

        posModA = {0, 0};
        posModB = {0, 0};
    }
};

TEST_F(CollisionHandlerTest, NoIntersection) {
    // Test when entities do not intersect
    // Adjust collider positions so they do not intersect
    entityB.getComponent<ColliderComponent>().collider.x = 20;
    entityB.getComponent<ColliderComponent>().collider.y = 20;

    auto intersections = collisionHandler.getIntersection(&entityA, &entityB, posModA, posModB);
    ASSERT_EQ(intersections.none(), true);
}

TEST_F(CollisionHandlerTest, IntersectionInAllDirections) {
    // Test when entities intersect in all directions
    // Adjust collider positions so they intersect in all directions
    entityB.getComponent<ColliderComponent>().collider.x = 5;
    entityB.getComponent<ColliderComponent>().collider.y = 5;

    auto intersections = collisionHandler.getIntersection(&entityA, &entityB, posModA, posModB);
    ASSERT_EQ(intersections.all(), true);
}

TEST_F(CollisionHandlerTest, IntersectionInSomeDirections) {
    // Test when entities intersect in some directions
    // Adjust collider positions so they intersect in some directions
    entityB.getComponent<ColliderComponent>().collider.x = 5;
    entityB.getComponent<ColliderComponent>().collider.y = 15;

    auto intersections = collisionHandler.getIntersection(&entityA, &entityB, posModA, posModB);
    ASSERT_EQ(intersections.test(static_cast<size_t>(Direction::UP)), true);
    ASSERT_EQ(intersections.test(static_cast<size_t>(Direction::DOWN)), false);
}