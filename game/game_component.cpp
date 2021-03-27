#include "../common.hpp"
#include "game_component.hpp"
#include "game.hpp"
#include "game_map.hpp"
#include "game_settings.hpp"
#include "game_io.hpp"

game::game_component::game_component(game_component* parent, const char* name) :
	parent_component(parent),
	component_name(name),
	position(0, 0),
	direction(direction_type::none)
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

game::game_io* game::game_component::get_game_io()
{
	game* game_instance = get_game_instance();
	if(!game_instance) return nullptr;

	return game_instance->get_io();
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

void game::game_component::set_direction(game_component::direction_type dir)
{
	direction = dir;
}

game::game_component::direction_type game::game_component::get_direction()
{
	return direction;
}

bool game::game_component::check_collision(game_component* requester, int x, int y)
{
	for(int i = 0; i < children.get_size(); i++)
		if(children[i] && children[i] != requester && children[i]->check_collision(requester, x, y))
			return true;

	return false;
}

bool game::game_component::check_game_collision(int x, int y)
{
	game* game_instance = get_game_instance();
	if(!game_instance) return false;

	return game_instance->check_collision(this, x, y);
}

game::game_component* game::game_component::get_child(int index)
{
	if(index < 0 || index >= children.get_size())
		return nullptr;
	return children[index];
}

int game::game_component::get_children_count()
{
	return children.get_size();
}

unsigned int game::game_component::get_tick_count()
{
	game* game_instance = get_game_instance();
	if(!game_instance) return 0;

	return game_instance->get_tick_count();
}
