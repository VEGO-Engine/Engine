#pragma once

#include <cstdint>

class Entity;

class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update(uint_fast16_t diffTime) {}

	virtual ~Component() = default;
};