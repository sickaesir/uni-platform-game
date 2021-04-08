#include "game_powerup.hpp"
#include "game_io.hpp"
#include "game_map.hpp"
#include "game_settings.hpp"

game::game_powerup::game_powerup(game_component* parent, powerup_type _type) :
	game_component(parent, game_component::component_type::powerup),
	type(_type),
	descend(true)
{
}

void game::game_powerup::tick()
{
	int render_x = pos_x() - get_game_map()->get_map_offset();
	if(render_x >= 0 && render_x <= get_game_settings()->get_game_width() && descend && get_tick_count() % 50 == 0)
	{
		if(!check_game_collision(render_x, pos_y() + 3))
			pos_y(pos_y() + 1);
		else
			descend = false;
	}
}

void game::game_powerup::render()
{
	char powerup_symbol = ' ';
	switch(type)
	{
		case powerup_type::heal:
			powerup_symbol = '+';
		break;
	}

	int render_x = pos_x() - get_game_map()->get_map_offset();

	if(render_x >= 0 && render_x <= get_game_settings()->get_game_width())
	{
		get_game_io()->draw(render_x, pos_y(), console::color::yellow, true, '/');
		get_game_io()->draw(render_x, pos_y() + 1, console::color::green, true, get_tick_count() % 2 ? '|' : '-');
		get_game_io()->draw(render_x, pos_y() + 2, console::color::yellow, true, '\\');
	}

	if(render_x + 1 >= 0 && render_x + 1 <= get_game_settings()->get_game_width())
	{
		get_game_io()->draw(render_x + 1, pos_y(), console::color::green, true, get_tick_count() % 2 ? '-' : '|');
		get_game_io()->draw(render_x + 1, pos_y() + 1, console::color::white, true, powerup_symbol);
		get_game_io()->draw(render_x + 1, pos_y() + 2, console::color::green, true, get_tick_count() % 2 ? '-' : '|');
	}

	if(render_x + 2 >= 0 && render_x + 2 <= get_game_settings()->get_game_width())
	{
		get_game_io()->draw(render_x + 2, pos_y(), console::color::yellow, true, '\\');
		get_game_io()->draw(render_x + 2, pos_y() + 1, console::color::green, true, get_tick_count() % 2 ? '|' : '-');
		get_game_io()->draw(render_x + 2, pos_y() + 2, console::color::yellow, true, '/');
	}
}
