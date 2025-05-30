#pragma once

class RenderManager;

class RenderObject
{
public:
	virtual void draw() = 0;

	RenderObject(int zIndex, RenderManager* renderManager);
	~RenderObject();

	int getZIndex() { return this->zIndex; };

	//! Comparitor to compare two ptr based on z-index
	struct ZIndexComparator {
		bool operator()(RenderObject const *lhs, RenderObject const *rhs ) const {
    		return lhs->zIndex < rhs->zIndex;
		}
	};

private:
	int zIndex = 0;

protected:
	RenderManager* renderManager;
};