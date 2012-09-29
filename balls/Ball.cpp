
#include <engine/components.h>
#include <engine/misc.h>
#include "Ball.h"
using namespace std;

Ball::Ball(Color4F color, Vector2F position, Vector2F acceleration)
{
	add_component(
		make_unique<CPosition2D>(position)
	);
	add_component(
		make_unique<CGeometry2D>(color, make_unique<Circle>(10.f))
	);
	add_component(
		make_unique<CVelocity2D>(acceleration, 0.f)
	);
	add_component(
		make_unique<CCollision>(true, false)
	);
	add_component(
		make_unique<CPhysics>()
	);
}
