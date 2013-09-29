#pragma once
#include "ISystem.h"

//Base class for systems which participate in dependency-based 
//automatic multithreading - which is not actually implemented yet

//To use, override at minimum on_wake and required_systems
//on_wake will be called each frame when the required systems have run
class ThreadedSystemBase : public ISystem
{
private:
	virtual void on_frame() final;
	virtual void on_message() override;
	virtual bool on_event(SDL_Event& event) override;
	virtual void on_wake() = 0;
	
public:
	ThreadedSystemBase();
	virtual ~ThreadedSystemBase();
	virtual std::vector<ISystem::ID> required_systems() const = 0;
	void add_entity(std::weak_ptr<IEntity> new_entity);
};

