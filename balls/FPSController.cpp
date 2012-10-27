#include <engine/core.h>
#include <engine/components.h>
#include "FPSController.h"
using namespace std;
using namespace glm;

vector<CMP> FPSController::required_components() const 
{
	array<CMP,2> compTypes = {CMP::Input, CMP::Transform};
	return vector<CMP>(compTypes.begin(), compTypes.end());
}

vector<SYS> FPSController::required_systems() const 
{
	array<SYS,0> sysTypes = {};
	return vector<SYS>(sysTypes.begin(), sysTypes.end());
}

FPSController::FPSController()
{
	_firstMouse = true;
	_yclamp = 0;
	SDL_WM_GrabInput(SDL_GRAB_ON);
}

bool FPSController::on_event(SDL_Event& event)
{
	auto character = entities[0].lock();
	auto transform = character->get_component<CTransform>();
	auto velocity = character->get_component<CVelocity>();
	auto input = character->get_component<CInput>();

	vec3 forward = transform->direction_vector();
	auto right = cross(forward, constants::y_axis);
	auto up = cross(right, forward);

	switch (event.type)
	{
		case SDL_MOUSEMOTION:
		{
			if (_firstMouse)
			{
				_firstMouse = false;
				return true;
			}

			//convert mouse delta to radians, clamping the y-axis to 180 degrees
			coord yrads = event.motion.yrel / (coord)120.0;
			coord xrads = event.motion.xrel / (coord)120.0;
			
			if (_yclamp + yrads > M_PI/2)
				yrads = (coord)M_PI/2 - (_yclamp + yrads);
			if (_yclamp + yrads < -M_PI/2)
				yrads = -((coord)M_PI/2 - (-_yclamp - yrads));
			_yclamp += yrads;

			//rotate around *global* Up, then around *local* Right
			quat pitch(eulers(yrads, 0, 0));
			quat yaw(eulers(0, -xrads, 0));
			transform->rotate = normalize(yaw * transform->rotate * pitch); 

			//move the cursor somewhere it can't bother us
			SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
			SDL_WarpMouse(500, 500);
			SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
			SDL_ShowCursor(SDL_DISABLE);

			return true;
		}

		case SDL_KEYDOWN:
		{
			_keys.insert(event.key.keysym.sym);
			vec3 direction = _calc_fb() * forward + _calc_lr() * right + _calc_ud() * up;
			if (length(direction) != 0)
				direction = normalize(direction) * input->speed;
			velocity->vector = direction;
			return true;
		}

		case SDL_KEYUP:
		{
			_keys.erase(event.key.keysym.sym);
			vec3 direction = _calc_fb() * forward + _calc_lr() * right + _calc_ud() * up;
			if (glm::length(direction) != 0)
				direction = normalize(direction) * input->speed;
			velocity->vector = direction;
			return true;
		}

		default:
			return false;
	}
}

bool FPSController::_key(SDLKey k)
{
	return _keys.find(k) != _keys.end();
}

coord FPSController::_calc_lr()
{
	coord result = 0;

	if (_key(SDLK_a))
		result -= 1;
	if (_key(SDLK_d))
		result += 1;

	return result;
}

coord FPSController::_calc_fb()
{
	coord result = 0;

	if (_key(SDLK_s))
		result -= 1;
	if (_key(SDLK_w))
		result += 1;

	return result;
}

coord FPSController::_calc_ud()
{
	coord result = 0;

	if (_key(SDLK_LSHIFT))
		result -= 1;
	if (_key(SDLK_SPACE))
		result += 1;

	return result;
}