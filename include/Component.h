#pragma once

class Entity;

class Component
{
public:
	Entity* entity;

	virtual void init()
	{
		// implementation in derived classes (when neccessary)
	}

	virtual void update()
	{
		// implementation in derived classes (when neccessary)
	}

	virtual void draw()
	{
		// implementation in derived classes (when neccessary)
	}

	virtual ~Component() = default;
};