#pragma once
#include "../core.h"

enum class CID
{
	Acceleration,
	Brush,
	Extents,
	Label,
    Mesh,
	Physics,
	Position,
	Velocity
};

class IComponent : public Identifiable<CID>
{
public:
	~IComponent() {}
};