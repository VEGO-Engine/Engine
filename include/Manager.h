#pragma once
#include <iostream>
#include <array>
#include <memory>
#include <vector>

#include "Constants.h"

class Entity;

class Manager
{
public:
	void update();
	void draw();
	void refresh();

	void addToGroup(Entity* mEntity, Group mGroup);
	std::vector<Entity*>& getGroup(Group mGroup);

	Entity& addEntity();

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, MAX_GROUPS> groupedEntities;
};