#include "game_character.hpp"
#include "../utils/runtime_utils.hpp"
#include "game_settings.hpp"
#include "game_io.hpp"

game::game_character::game_character(game_component* parent) : game_component(parent, "game_character"),
	walking_direction(0)
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
	render_head();
	render_body();
	render_left_arm();
	render_right_arm();
	render_left_leg();
	render_right_leg();
}

void game::game_character::render_head()
{
	get_game_io()->draw(pos_x() + 1, pos_y() - 2, console::color::yellow, true, 'o');
}

void game::game_character::render_body()
{
	get_game_io()->draw(pos_x() + 1, pos_y() - 1, console::color::green, true, '#');
}

void game::game_character::render_left_arm()
{
	char left_arm_char = '<';
	switch(get_direction())
	{
		case game_component::direction_type::right:
			left_arm_char = pos_x() % 4 ? '/' : '<';
		break;
		case game_component::direction_type::left:
			left_arm_char = pos_x() % 4 ? '\'' : '-';
	}

	get_game_io()->draw(pos_x(), pos_y() - 1, console::color::blue, true, left_arm_char);
}

void game::game_character::render_right_arm()
{
	char right_arm_char = '>';

	switch(get_direction())
	{
		case game_component::direction_type::right:
			right_arm_char = pos_x() % 4 ? '\'' : '-';
		break;
		case game_component::direction_type::left:
			right_arm_char = pos_x() % 4 ? '\\' : '>';
		break;
	}

	get_game_io()->draw(pos_x() + 2, pos_y() - 1, console::color::blue, true, right_arm_char);
}

void game::game_character::render_left_leg()
{
	get_game_io()->draw(pos_x(), pos_y(), console::color::blue, true, '/');
}

void game::game_character::render_right_leg()
{
	get_game_io()->draw(pos_x() + 2, pos_y(), console::color::blue, true, '\\');
}

bool game::game_character::on_keyboard(int character)
{
	switch(character)
	{
		case -1: // no key pressed
		{
		}
		break;


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
	set_direction(game_component::direction_type::right);
}

void game::game_character::on_left_arrow()
{
	pos_x(pos_x() - 1);
	set_direction(game_component::direction_type::left);
}
