#pragma once
#include <core/framework.h>
#include <mesh/geometry.h>
#include "scene.h"

class RenderSystem final : public Identified<RenderSystem,ISystem>, public IGraphWalker
{
	std::shared_ptr<IRenderer> _renderer;
	SceneGraph _scene;

	void on_entity(std::weak_ptr<IEntity> entity) override;
    void on_frame() override;
	bool on_event(SDL_Event& event) override;

public:
    std::string description() const final;
    virtual std::vector<ISystem::ID> required_systems() const override;
    
    RenderSystem(std::shared_ptr<IRenderer>);

	void visit(RootNode*) override;
	void visit(BranchNode*) override;
	void visit(LeafNode*) override;
};

