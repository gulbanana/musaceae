#include "ISystem.h"
#include <algorithm>
using namespace std;

void ISystem::add_entity(weak_ptr<IEntity> new_entity)
{ 
	entities.push_back(new_entity); 
}

void ISystem::frame()
{
	on_frame();

	remove_if(begin(entities), end(entities), [](weak_ptr<IEntity> entity)
	{
		return entity.expired();
	});

	for_each(begin(entities), end(entities), [=](weak_ptr<IEntity> entity)
	{
		on_entity(entity.lock());
	});
}