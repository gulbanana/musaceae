#pragma once
#include <core/framework.h>
#include <tile/types.h>
#include <core/text/FontManager.h>
#include <SDL_video.h>
#include "IBlitter.h"

class GLBlitSystem : public Identified<GLBlitSystem, ISystem, ThreadedSystemBase>, public IBlitter
{
private:
	grid _tram;
	SDL_Surface* _surface;
	FontManager* _fonts;
	unsigned int _width;
	unsigned int _height;
	float _font_size;

	std::vector<ISystem::ID> required_systems() const override;
	void on_wake() override;
	bool on_event(SDL_Event&) override;

	void resize();

public:
	GLBlitSystem(unsigned int pixelWidth, unsigned int pixelHeight);
	~GLBlitSystem();

	grid* get_tram() override;
};

