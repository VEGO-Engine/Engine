#include "RenderObject.h"
#include "RenderManager.h"

RenderObject::RenderObject(int zIndex, RenderManager& renderManager) : zIndex(zIndex), renderManager(renderManager) {
	renderManager.add(this);
}

RenderObject::~RenderObject() { 
	this->renderManager.remove(this);
}