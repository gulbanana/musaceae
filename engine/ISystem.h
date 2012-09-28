#pragma once
#include <memory>
#include <vector>
#include <string>
#include <typeinfo>
#include "IEntity.h"



class ISystem
{
	IDENTIFIABLE
	(
		Collision,
		Input,
		Display,
		Movement,
		ShapeRender,
		UIRender
	);

private:
	virtual void on_frame() {}
	virtual void on_entity(std::shared_ptr<IEntity> entity) {}

protected:
	std::vector<std::weak_ptr<IEntity>> entities;

public:
	virtual ~ISystem() {}
	virtual std::vector<IComponent::ID> required_components() { return std::vector<IComponent::ID>(); }
	virtual void add_entity(std::weak_ptr<IEntity> new_entity);
	
	void frame();
};

