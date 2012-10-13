#include <array>
#include <algorithm>
#include <vector>
#include <iostream>
#include <engine/misc.h>
#include <engine/components.h>
#include "Bouncer.h"
using namespace std;

vector<IComponent::ID> Bouncer::required_components() const
{
	array<CMP,4> compTypes = {CMP::Physics, CMP::Velocity, CMP::Position, CMP::Mesh};
	return vector<CMP>(compTypes.begin(), compTypes.end());
}

vector<ISystem::ID> Bouncer::required_systems() const
{
	array<SYS,3> compTypes = {SYS::Collision};
	return vector<SYS>(compTypes.begin(), compTypes.end());
}

Bouncer::Bouncer(int r) : _width((coord)r), _height((coord)r), _depth((coord)r)  {}

Bouncer::Bouncer(int x, int y, int z) : _width((coord)x), _height((coord)y), _depth((coord)z)  {}

void Bouncer::on_entity(std::shared_ptr<IEntity> entity)
{
	auto physics = entity->get_component<CPhysics>();
	if (!physics->can_collide) return;

	auto position = entity->get_component<CPosition>();
	auto velocity = entity->get_component<CVelocity>();
	auto mesh = entity->get_component<CMesh>();

	//Bounce type #1: walls, reflect by component inversion
	auto sourceBox = mesh->geometry->bounds();
	bool outOfBoundsX = sourceBox.left() + position->location.x <= 0.f ||
						sourceBox.right() + position->location.x >= _width;
	bool outOfBoundsY = sourceBox.bottom() + position->location.y <= 0.f ||
						sourceBox.top() + position->location.y >= _height;
	bool outOfBoundsZ = sourceBox.back() + position->location.z <= 0.f ||
						sourceBox.front() + position->location.z >= _depth;

	if (outOfBoundsX) 
	{
		velocity->vector.x *= -1;
        position->location.x = max(position->location.x, sourceBox.right());
        position->location.x = min(position->location.x, _width - sourceBox.right());
	}
		
	if (outOfBoundsY) 
	{
		velocity->vector.y *= -1;
        position->location.y = max(position->location.y, sourceBox.top());
        position->location.y = min(position->location.y, _height - sourceBox.top());
	}

	if (outOfBoundsZ) 
	{
		velocity->vector.z *= -1;
        position->location.z = max(position->location.z, sourceBox.front());
        position->location.z = min(position->location.z, _depth - sourceBox.front());
	}

	if (outOfBoundsX || outOfBoundsY || outOfBoundsZ)
	{
		return;
	}

	//Bounce type #2: objects, reflect by angle of target
	for (auto target : physics->collisions)
	{		
		auto targetPosition = target->get_component<CPosition>();

		//calculate angle of collision
		auto speed = velocity->vector.length();
		auto angleOfCollision = targetPosition->location - position->location;
		angleOfCollision.normalize();

		velocity->vector = angleOfCollision * (coord)-1 * speed;

		if (target->has_component<CVelocity>())
		{
			auto targetVelocity = target->get_component<CVelocity>();
			auto targetSpeed = targetVelocity->vector.length();

			//swap velocity
			if (targetSpeed > (coord)0)
			{
				velocity->vector.normalize();
				velocity->vector *= targetSpeed;

				targetVelocity->vector.normalize();
				targetVelocity->vector *= speed;
			}
			
			//equalise velocity
			/*if (targetSpeed > (coord)0)
			{
				auto speedDifference = (coord)(abs(speed - targetSpeed) / 2);

				if (speed > targetSpeed)
				{
					velocity->vector.normalize();
					targetVelocity->vector.normalize();
					velocity->vector *= speed - speedDifference;
					targetVelocity->vector *= targetSpeed + speedDifference;
				}

				if (targetSpeed > speed)
				{
					velocity->vector.normalize();
					targetVelocity->vector.normalize();
					velocity->vector *= speed + speedDifference;
					targetVelocity->vector *= targetSpeed - speedDifference;
				}
			}*/
			
		}
		
		return;
	}
}