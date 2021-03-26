#include "game_character.hpp"
#include "../utils/runtime_utils.hpp"
#include "game_settings.hpp"

game::game_character::game_character(game_component* parent) : game_component(parent, "game_character")
{
}

game::game_character::~game_character()
{
}

void game::game_character::tick()
{
	if(pos_x() == 0 && pos_y() == 0)
	{
		log("position was 0:0, initializing based on map...");
		initialize_position();
	}
}

void game::game_character::initialize_position()
{
	game_map* map = get_game_map();
	runtime_assert(map, "failed to initialize position, map n/a");

	game_settings* settings = get_game_settings();
	runtime_assert(settings, "failed to initialize position, settings n/a");

	int game_height = settings->get_game_height();
	int char_y = game_height - settings->get_map_wall_padding() - 1;
	int char_x = settings->get_map_wall_padding() + 10;

	pos_y(char_y); pos_x(char_x);

	log("character position initialized, x:%d y:%d", char_x, char_y);
}

void game::game_character::render()
{
	move(pos_y() - 2, pos_x());
	printw(" o ");
	move(pos_y() - 1, pos_x());
	printw("<#>");
	move(pos_y(), pos_x());
	printw("/ \\");
}

bool game::game_character::on_keyboard(int character)
{
	switch(character)
	{
		case 0x43: // right arrow
		{
			on_right_arrow();
			return true;
		}
		break;

		case 0x44: // left arrow
		{
			on_left_arrow();
			return true;
		}
		break;
	}
	return false;
}

void game::game_character::on_right_arrow()
{
	pos_x(pos_x() + 1);
}

void game::game_character::on_left_arrow()
{
	pos_x(pos_x() - 1);
}
