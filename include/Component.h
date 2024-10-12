#pragma once

#include <string>

class Entity;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual std::string componentName() = 0;

	virtual ~Component() = default;
};