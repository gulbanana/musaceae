#include <typeinfo>
#include <ctime>
#include <algorithm>
#include <SDL.h>
#include "misc.h"
#include "systems.h"
#include "World.h"
#include "GameState.h"
using namespace std;

#pragma region sdlcall
void check(std::function<int()> sdlCall)
{
	int rc = sdlCall();
	if (rc != 0)
		throw std::runtime_error(SDL_GetError());
}

template<typename T>
T check(std::function<T()> sdlCall)
{
	T ret = sdlCall();
	if (ret == nullptr)
		throw std::runtime_error(SDL_GetError());
	return ret;
}
#pragma endregion

#pragma region pimpl
class WorldImpl
{
	static const unsigned maxFPS = 60;

	SDL_Surface* surface;
	shared_ptr<GameState> state;
	vector<unique_ptr<ISystem>> systems;
	vector<shared_ptr<IEntity>> entities;
	
	void frame();

public:
	WorldImpl(const string title, int width, int height);
	void add_entity(shared_ptr<IEntity> entity);
	void add_system(unique_ptr<ISystem> system);
	void play();
};
#pragma endregion

World::World(const string title) : _pimpl(new WorldImpl(title, 800, 600)) {}
WorldImpl::WorldImpl(const string title, int width, int height)
{
	state = make_shared<GameState>();

	check([]{ return SDL_Init(SDL_INIT_EVERYTHING); });
	SDL_WM_SetCaption(title.c_str(), nullptr);
	check([]{ return SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); });
	check([]{ return SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); });
	check([]{ return SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); });
	surface = check<SDL_Surface*>([=]{ return SDL_SetVideoMode(width, height, 32, SDL_OPENGL); });

	add_system(make_unique<ControlSystem>(state));
	add_system(make_unique<MotionSystem>(state, width, height));
	add_system(make_unique<CollisionSystem>());
	add_system(make_unique<PhysicsSystem>());
	add_system(make_unique<RenderSystem>(width, height));
	add_system(make_unique<UISystem>(state));
}

void World::play() { _pimpl->play(); }
void WorldImpl::play()
{
	unsigned next, mspf = 1000 / maxFPS;
	state->clock = SDL_GetTicks();
	
	while (!state->shouldQuit)
	{
		frame();
		next = state->clock + mspf;
		state->clock = SDL_GetTicks();
		state->fps = 1000 / (state->clock - (next-mspf));
		if (state->clock < next)
			SDL_Delay(next - state->clock);
	}

	SDL_Quit();
}

void World::add_entity(shared_ptr<IEntity> entity) { _pimpl->add_entity(entity); }
void WorldImpl::add_entity(shared_ptr<IEntity> entity)
{
	entities.push_back(entity);

	for (auto& system : systems)
	{
		auto comps = system->required_components();
		if (comps.size() == 0) continue;

		int matches = count_if(comps.begin(), comps.end(), [&](IComponent::ID requirement)
		{
			return entity->has_component(requirement);
		});

		if (matches == comps.size())
			system->add_entity(entity);
	}
}

void WorldImpl::add_system(unique_ptr<ISystem> system)
{
	systems.push_back(std::move(system));
}

void WorldImpl::frame()
{
	for(auto& system : systems)
	{
		system->frame();
	}
}