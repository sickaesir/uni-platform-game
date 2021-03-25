#include "../common.hpp"
#include "game_component.hpp"
#include "game.hpp"

game::game_component::game_component(game_component* parent, const char* name) :
	parent_component(parent),
	component_name(name)
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

void game::game_component::log(const char* format, ...)
{
	game* game_instance = get_game_instance();
	if(!game_instance) return;

	char buffer[256];
	sprintf(buffer, "[%s] [0x%p] %s\n\r", component_name, this, format);

	va_list args;
	va_start(args, format);
	game_instance->write_log(buffer, args);
	va_end(args);
}

