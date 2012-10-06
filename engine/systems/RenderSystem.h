#pragma once
#include <engine/core.h>
#include <engine/geometry.h>
#include <engine/scene.h>

class RenderSystem : public Identified<ISystem,SYS::Render>, public IGraphWalker
{
	std::shared_ptr<IRenderer> _renderer;
	std::weak_ptr<RootNode> _scene;

	void add_entity(std::weak_ptr<IEntity> entity) override;
	void on_frame() override;
	bool on_event(SDL_Event& event) override;

public:
	RenderSystem(std::shared_ptr<IRenderer>);

	std::vector<IComponent::ID> required_components() const override;
	virtual std::vector<ISystem::ID> required_systems() const override;

	void visit(LeafNode*) override;
	void visit(BranchNode*) override;
};
