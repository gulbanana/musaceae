#include <tile/stdafx.h>
#include <tile/components.h>
#include "RenderSystem.h"
#include "KBMControlSystem.h"
#include "PadControlSystem.h"
#include <algorithm>
using namespace std;

vector<ISystem::ID> RenderSystem::required_systems() const
{
	return ISystem::require<KBMControlSystem, PadControlSystem>();
}

std::vector<IComponent::ID> RenderSystem::required_components() const
{
    return IComponent::require<CDraw, CTransform>();
}

RenderSystem::RenderSystem(IBlitter* blitter, shared_ptr<GameState> state) : _blitter(blitter), _state(state) 
{
    _cam_centre_x = 0;
    _cam_centre_y = 0;
    _cam_z = 0;
}

RenderSystem::~RenderSystem() {}

void RenderSystem::on_frame_start()
{
	_tram = _blitter->get_tram();

	_tram->fill(tile('.'));

    _cam_left = _cam_centre_x - _tram->width/2;
    _cam_bottom = _cam_centre_y - _tram->height/2;
    _cam_right = _cam_left + _tram->width;
    _cam_top = _cam_bottom + _tram->height;
}

void RenderSystem::on_frame_entity(std::shared_ptr<IEntity> e)
{
    auto transform = e->get_component<CTransform>();
    
    if (!within_camera_bounds(transform->translate)) return;

    auto drawable = e->get_component<CDraw>();
    _tram->draw(drawable->layout, transform->translate.x - _cam_left, transform->translate.y - _cam_bottom);
}

bool RenderSystem::within_camera_bounds(point p)
{
    return p.x >= _cam_left && p.y >= _cam_bottom &&
           p.x <= _cam_right && p.y <= _cam_top;
}