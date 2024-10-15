#pragma once

#include <vector>

#include "RenderObject.h"

class RenderManager {
public:
	RenderManager() {};

	void remove(RenderObject* obj);
	void add(RenderObject* obj);

	void renderAll();

private:
	std::vector<RenderObject*> renderObjects;
	bool isSorted;
};