#include "RenderSystem.h"
#include "Position2D.h"
#include "Drawable.h"
#include <array>
#include <iterator>
#include <typeinfo>
using namespace std;

vector<string> RenderSystem::required_components()
{
	array<string,2> compTypes = {"Position2D", "Drawable"};
	return vector<string>(compTypes.begin(), compTypes.end());
}

RenderSystem::RenderSystem(sf::RenderTarget* s) : surface(s)
{
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");
}

void RenderSystem::on_frame()
{
	surface->clear();

	for_each(begin(entities), end(entities), [=](weak_ptr<IEntity> entity)
	{
		auto view = entity.lock();
		auto position = (Position2D*)view->get_component("Position2D").get();
		auto content = (Drawable*)view->get_component("Drawable").get();

		auto entityTranslation = sf::Transform();
		
		sf::CircleShape shape(100.f);
		shape.setFillColor(content->color);
		entityTranslation.translate(position->x, position->y);
		surface->draw(shape, sf::RenderStates(entityTranslation));

		sf::Text greeting(content->text, font);
		entityTranslation.translate(75.f, 75.f);
		surface->draw(greeting, sf::RenderStates(entityTranslation));
	});
}

void RenderSystem::on_entity(shared_ptr<IEntity> entity)
{
	auto position = (Position2D*)entity->get_component("Position2D").get();
	auto content = (Drawable*)entity->get_component("Drawable").get();

	auto entityTranslation = sf::Transform();
		
	sf::CircleShape shape(100.f);
	shape.setFillColor(content->color);
	entityTranslation.translate(position->x, position->y);
	surface->draw(shape, sf::RenderStates(entityTranslation));

	sf::Text greeting(content->text, font);
	entityTranslation.translate(75.f, 75.f);
	surface->draw(greeting, sf::RenderStates(entityTranslation));
}