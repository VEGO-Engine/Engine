#include "RenderManager.h"
#include "RenderObject.h"
#include <algorithm>

void RenderManager::renderAll()
{
	if (!this->isSorted) {
		std::ranges::sort(this->renderObjects, RenderObject::ZIndexComparator());
	}
	for (RenderObject* obj : this->renderObjects) {
		obj->draw();
	}
}

void RenderManager::add(RenderObject* renderObject) {
	this->renderObjects.emplace_back(renderObject);
	this->isSorted = false;
}

void RenderManager::remove(RenderObject* renderObject)
{
	this->renderObjects.erase(std::remove(this->renderObjects.begin(), this->renderObjects.end(), renderObject), this->renderObjects.end());
	this->isSorted = false;
}