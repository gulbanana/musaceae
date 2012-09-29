#pragma once
#include "IComponent.h"

class CPosition2D : public IComponent
{
public:
	static const ID ID = ID::Position2D;
	Vector2F current;
	Vector2F previous;

	CPosition2D(float x, float y) : current(x, y), previous(x, y) {}
	CPosition2D(Vector2F pos) : current(pos), previous(pos) {}
};

