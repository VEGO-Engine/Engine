#pragma once

class Entity;

enum class GroupLabel
{
	MAP,
	PLAYERS,
	ENEMIES,
	COLLIDERS,
    PROJECTILE,
    HEARTS
};

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() = default;
};