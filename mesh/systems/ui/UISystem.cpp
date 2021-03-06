#include <mesh/stdafx.h>
#include "UISystem.h"
#include "UISystemImpl.h"
#include "../render/RenderSystem.h"
using namespace std;

string UISystem::description() const
{
    return "UI manager";
}

vector<ISystem::ID> UISystem::required_systems() const 
{
	return require<RenderSystem>();
}

UISystem::UISystem(GameState* s) : _pimpl(new UISystemImpl(s)) {}

void UISystem::on_frame()
{
	_pimpl->on_frame();
}

bool UISystem::on_event(SDL_Event& event)
{
	return _pimpl->on_event(event);
}