#include "../common.hpp"
#include "game_component.hpp"
#include "game.hpp"
#include "game_map.hpp"
#include "game_settings.hpp"
#include "game_io.hpp"

game::game_component::game_component(game_component* parent, component_type _type) :
	parent_component(parent),
	position(0, 0),
	direction(direction_type::none),
	type(_type)
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

game::game_character* game::game_component::get_game_character()
{
	game* game_instance = get_game_instance();
	if(!game_instance) return nullptr;

	return game_instance->get_character();
}

game::game_component::component_type game::game_component::get_type()
{
	return type;
}

const char* game::game_component::get_type_str()
{
	switch(get_type())
	{
		case component_type::game: return "game";
		case component_type::character: return "character";
		case component_type::io: return "io";
		case component_type::laser: return "laser";
		case component_type::map: return "map";
		case component_type::rock: return "rock";
		case component_type::powerup: return "powerup";
		case component_type::trooper: return "trooper";
		case component_type::flyier: return "flyier";
		case component_type::menu: return "menu";
		default: return "n/a";
	}
}

void game::game_component::log(const char* format, ...)
{
	game* game_instance = get_game_instance();
	if(!game_instance) return;

	char buffer[256];
	sprintf(buffer, "[%s] [0x%p] %s", get_type_str(), this, format);

	va_list args;
	va_start(args, format);
	game_instance->write_log(buffer, args);
	va_end(args);
}

void game::game_component::tick()
{
	for(int i = 0; i < invalidated_children.get_size(); i++)
	{
		remove_component(invalidated_children[i]);
	}

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

game::game_component* game::game_component::check_collision(game_component* requester, int x, int y)
{
	for(int i = 0; i < children.get_size(); i++)
	{
		if(children[i] && children[i] != requester)
		{
			game_component* collided_component = children[i]->check_collision(requester, x, y);
			if(!collided_component) continue;

			return collided_component;
		}
	}

	return nullptr;
}

game::game_component* game::game_component::check_game_collision(int x, int y)
{
	game* game_instance = get_game_instance();
	if(!game_instance) return nullptr;

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

void game::game_component::remove_component(game_component* component)
{
	for(int i = 0; i < get_children_count(); i++)
	{
		if(children[i] == component)
			children.remove_at(i);
	}
}

void game::game_component::invalidate()
{
	if(!parent_component) return;
	parent_component->invalidated_children.add(this);
}

bool game::game_component::is_enemy()
{
	return get_type() >= enemy_start && get_type() <= enemy_end;
}

void game::game_component::clear_children()
{
	while(get_children_count())
		remove_component(get_child(0));
}
