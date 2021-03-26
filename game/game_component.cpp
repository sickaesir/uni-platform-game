#include "../common.hpp"
#include "game_component.hpp"
#include "game.hpp"
#include "game_map.hpp"
#include "game_settings.hpp"

game::game_component::game_component(game_component* parent, const char* name) :
	parent_component(parent),
	component_name(name),
	position(0, 0)
{
}

game::game_component* game::game_component::get_parent()
{
	return parent_component;
}

game::game* game::game_component::get_game_instance()
{
	game_component* component = this;
	while(true)
	{
		game_component* parent = component->get_parent();
		if(!parent)
			return (game*)component;

		component = parent;
	}
}

game::game_settings* game::game_component::get_game_settings()
{
	game* game_instance = get_game_instance();
	if(!game_instance)
		return nullptr;

	return game_instance->get_settings();
}

game::game_map* game::game_component::get_game_map()
{
	game* game_instance = get_game_instance();
	if(!game_instance) return nullptr;

	return game_instance->get_map();
}

void game::game_component::log(const char* format, ...)
{
	game* game_instance = get_game_instance();
	if(!game_instance) return;

	char buffer[256];
	sprintf(buffer, "[%s] [0x%p] %s", component_name, this, format);

	va_list args;
	va_start(args, format);
	game_instance->write_log(buffer, args);
	va_end(args);
}

void game::game_component::tick()
{
	children.for_each([](int idx, game_component* component) {
		if(!component) return;
		component->tick();
	});
}

void game::game_component::render()
{
	children.for_each([](int idx, game_component* component) {
		if(!component) return;
		component->render();
	});
}

bool game::game_component::on_keyboard(int keyboard_key)
{
	for(int i = 0; i < children.get_size(); i++)
		if(children[i] && children[i]->on_keyboard(keyboard_key))
			return true;
	return false;
}

void game::game_component::add_component(game_component* component)
{
	children.add(component);
}

void game::game_component::pos_x(int x)
{
	position.x(x);
}

void game::game_component::pos_y(int y)
{
	position.y(y);
}

int game::game_component::pos_x()
{
	return position.x();
}

int game::game_component::pos_y()
{
	return position.y();
}
