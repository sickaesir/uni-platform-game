#include "game_powerup.hpp"
#include "game_io.hpp"

game::game_powerup::game_powerup(game_component* parent, powerup_type _type) :
	game_component(parent, game_component::component_type::powerup),
	type(_type)
{
}

void game::game_powerup::tick()
{
	
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

	get_game_io()->draw(pos_x(), pos_y(), console::color::yellow, true, '/');
	get_game_io()->draw(pos_x() + 1, pos_y(), console::color::green, true, '-');
	get_game_io()->draw(pos_x() + 2, pos_y(), console::color::yellow, true, '\\');
	get_game_io()->draw(pos_x(), pos_y() + 1, console::color::green, true, '|');
	get_game_io()->draw(pos_x() + 1, pos_y() + 1, console::color::white, true, powerup_symbol);
	get_game_io()->draw(pos_x() + 2, pos_y() + 1, console::color::green, true, '|');
	get_game_io()->draw(pos_x(), pos_y() + 2, console::color::yellow, true, '\\');
	get_game_io()->draw(pos_x() + 1, pos_y() + 2, console::color::green, true, '-');
	get_game_io()->draw(pos_x() + 2, pos_y() + 2, console::color::yellow, true, '/');
}
