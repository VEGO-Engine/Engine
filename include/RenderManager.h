#pragma once

#include <vector>

#include "RenderObject.h"

class RenderManager {
public:
	RenderManager() {};

	/*
	 * Remove an object from the list of objects to be rendered
	 * \param renderObject The object to be removed
	 * \sa RenderObject
	 */
	void remove(RenderObject* obj);
	/*
	 * Add an object to be rendered
	 * \param renderObject The object to be rendered
	 * \sa RenderObject
 	 */
	void add(RenderObject* obj);

	void renderAll(); //!< Render all objects. If the list has been modified, sorts it based on z-index first

private:
	std::vector<RenderObject*> renderObjects;
	bool isSorted;
};