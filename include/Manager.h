#pragma once

#include <iostream>

#include <array>
#include <memory>
#include <vector>

#include "Constants.h"
#include "Entity.h"

class Game;
class Manager
{
public:
	Manager(Game* game) : game(game) {};

	void update();
	void draw();
	void refresh();

	void addToGroup(Entity* mEntity, Group mGroup);
	std::vector<Entity*>& getGroup(Group mGroup);

	void addToTeam(Entity* mEntity, Team mTeam);
	std::vector<Entity*>& getTeam(Team mTeam);

	std::vector<Entity*> getAll();

	Entity& addEntity();

	Game* getGame() { return this->game; };

private:
	Game* game;
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, MAX_GROUPS> entitiesByGroup;
	std::array<std::vector<Entity*>, MAX_TEAMS> entitiesByTeam;
};