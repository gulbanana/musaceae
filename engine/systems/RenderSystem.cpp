#include <array>
#include <iterator>
#include <SDL_opengl.h>
#include <engine/components.h>
#include "RenderSystem.h"
using namespace std;

vector<CMP> RenderSystem::required_components() const 
{
	array<CMP,1> compTypes = {CMP::Scene};
	return vector<CMP>(compTypes.begin(), compTypes.end());
}

vector<SYS> RenderSystem::required_systems() const 
{
	array<SYS,2> sysTypes = {SYS::Motion, SYS::Logic};
	return vector<SYS>(sysTypes.begin(), sysTypes.end());
}

RenderSystem::RenderSystem(shared_ptr<IRenderer> r) : _renderer(r) {}

void RenderSystem::add_entity(weak_ptr<IEntity> new_entity)
{ 
	_scene = static_pointer_cast<RootNode>(new_entity.lock()); 
}

bool RenderSystem::on_event(SDL_Event& event)
{
	if (event.type == SDL_VIDEORESIZE)
		_renderer->resize(event.resize.w, event.resize.h);
	
	return false;
}

void RenderSystem::on_frame()
{
	auto graph = _scene.lock();

	_renderer->begin_frame();
	graph->accept(this);
	_renderer->end_frame();
}

void RenderSystem::visit(BranchNode* node)
{
	for (auto child : node->children)
		child->accept(this);
}

void RenderSystem::visit(LeafNode* node)
{
	if (node->has_component<CMesh>())
	{
		auto mesh = node->get_component<CMesh>();
		auto position = node->get_component<CPosition>();
		mesh->geometry->accept(_renderer.get(), position->location, position->orientation);
	}
}