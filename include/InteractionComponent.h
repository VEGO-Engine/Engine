#pragma once

#include "Component.h"
#include "Entity.h"

#include <vector>
#include <functional>

class InteractionComponent : public Component
{
public:
    InteractionComponent(bool canInteract, bool isInteractable, int reach);
    ~InteractionComponent();

    void init() override;
    void update();

    /*!
     * \brief Checks if two entities can interact with each other
     * \param interactor The source of the interaction
     * \param interactee The target of the interaction
     * \return A boolean if an interaction is possible
     */
    bool interact(Entity* interactor, Entity* interactee);

    /*!
     * \brief Find the closest entity the interactor could interact with
     * \param direction The direction in which the interactor is facing, the interactor can only interact with entities in the direction it is facing
     * \param interactor The initiator of the interaction
     * \param entities A list of entities
     * \return The interactable entity closest to the interactor
     */
    Entity* getClosestInteractableEntity(Direction direction, Entity* interactor, std::vector<Entity*> entities);

private:
    bool canInteract;
    bool isInteractable;

    int reach;

    /*!
     * \brief Find the entity closest to the interactor
     * \param entities A list of entities
     * \param interactorT TransformComponent of the interactor (contains the coordinates)
     * \param direction The direction the interactor is facing
     * \return The closest entity
     */
    Entity* findClosestEntity(std::vector<Entity*>& entities, TransformComponent& interactorT, Direction direction);

    /*!
     * \brief Checks if an entity is in the direction the interactor faces
     * \param direction The direction the interactor is facing
     * \param interactorT TransformComponent of the interactor (contains the coordinates)
     */
    std::function<bool(const TransformComponent&)> getDirectionalCheck(Direction direction, const TransformComponent& interactorT);

    /*!
     * \brief Checks if entity is within reach of the interactor
     * \param interactorT TransformComponent of the interactor (contains the coordinates)
     * \param entityT TransformComponent of the entity (contains the coordinates)
     * @param direction The direction the interactor is facing
     * @return
     */
    bool isEntityCloseEnough(const TransformComponent& interactorT, const TransformComponent& entityT, Direction direction);

    /*!
     * \brief Calculates distance between entity and interactor
     * \param iPos Coordinates of the interactor
     * \param ePos Coordinates of the entity
     * \return The distance between interactor and entity
     */
    float calculateDistance(Vector2D iPos, Vector2D ePos);
};