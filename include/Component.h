#pragma once

class Entity;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}

	virtual ~Component() = default;
};