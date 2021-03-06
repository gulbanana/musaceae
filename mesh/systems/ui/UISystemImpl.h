#pragma once
#include <core/GameState.h>
#include <SDL_events.h>
#include <guichan/guichan.hpp>

class UISystemImpl
{
	GameState* _state;

	//guichan objects
	std::unique_ptr<gcn::Gui> _gui;
	std::unique_ptr<gcn::Input> _input;
	std::unique_ptr<gcn::Graphics> _graphics;
	
	//the entire gui!
	std::unique_ptr<gcn::Label> _fpsLabel;

	//pimpl passthrough
public:
	UISystemImpl(GameState* s);
	void on_frame();
	bool on_event(SDL_Event& event);
};
