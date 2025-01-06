#pragma once

#include "Entity.h"
#include "Map.h"
#include <functional>
#include <memory>
#include <vector>

class Scene {
public:
    /**
     * @brief      Adds an Entity limited to the scene
     * @details    Adds an Entity, that is limited to the scene only. The entity will be destroyed with the seen, and should not be accessed afterward. For Entities that need to be reset to a specific position when loading a scene, use addInitFunc. Entities will respawn with the same parameters each time the scene is initialized.
     * @param[in]  entityDefinition  Function to define the entity. The function will only be called when the scene will be initialized
     */
    void addEntity(std::function<Entity*()> entityDefinition);
    /**
     * @brief      Adds an Entity limited to this cycle of the scene
     * @details    Adds an Entity, that is limited to the scene only. The entity will be destroyed with the seen, and should not be accessed afterward. For Entities that need to be reset to a specific position when loading a scene, use addInitFunc. Entities will only spawn once.
     * @param[in]  entityDefinition  Function to define the entity. The function will only be called when the scene will be initialized
     */
    void addTemporaryEntity(std::function<Entity*()> entityDefinition);
    /**
     * @brief      Adds a function to be executed on init of the scene.
     *
     * @param[in]  initFunc  The initialize function
     */
    void addInitFunc(std::function<void()> initFunc);
    /**
     * @brief      Adds a function to be executed on update of the scene.
     *
     * @param[in]  updateFunc  The update function
     */
    void addUpdateFunc(std::function<void(uint_fast16_t diffTime)> updateFunc);
    /**
     * @brief      Adds a function to be executed on reset of the scene.
     *
     * @param[in]  resetFunc  The reset function
     */
    void addResetFunc(std::function<void()> resetFunc);

    void addMap(Map* map);
    void addMap(const char* path);

    void init();
    void update(uint_fast16_t diffTime);
    void reset();

    bool isActive() { return this->active; };
private:
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::weak_ptr<Entity>> tempEntities;
    std::vector<std::function<Entity*()>> entityFuncs;
    std::vector<std::function<Entity*()>> tempEntityFuncs;
    std::vector<std::function<void()>> initFuncs;
    std::vector<std::function<void(uint_fast16_t diffTime)>> updateFuncs;
    std::vector<std::function<void()>> resetFuncs;

    std::unique_ptr<Map> map_unique; // only used if map is constructed by scene
    Map* map = nullptr;

    bool active = false;
};