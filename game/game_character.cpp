#include "game_character.hpp"
#include "../utils/runtime_utils.hpp"
#include "game_settings.hpp"
#include "game_io.hpp"
#include "game_map.hpp"

game::game_character::game_character(game_component* parent) : game_component(parent, "game_character")
	, jump_velocity(0)
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
		return;
	}

	jump_tick();
}

void game::game_character::jump_tick()
{
	if(get_tick_count() % get_game_settings()->get_gravity_ticks())
		return;

	if(!jump_velocity)
	{
		if(check_game_collision(pos_x(), pos_y() + 1))
			return;
//		log("no collision at y:%d, descending by 1 unit", pos_y() + 1);
		pos_y(pos_y() + 1);
		return;
	}

	if(check_game_collision(pos_x(), pos_y() - 3))
	{
		log("found collision at next y (%d), jump aborted", pos_y() - 1);
		jump_velocity = 0;
		return;
	}

	jump_velocity--;
	pos_y(pos_y() - 1);

	if(!jump_velocity)
		log("jump velocity points resetted, ending jump");
}

void game::game_character::initialize_position()
{
	game_settings* settings = get_game_settings();
	runtime_assert(settings, "failed to initialize position, settings n/a");

	int game_height = settings->get_game_height();
	int char_y = game_height - settings->get_map_wall_padding() - 1;
	int char_x = settings->get_map_wall_padding() + 10;

	pos_y(char_y); pos_x(char_x);
	jump_velocity = 0;

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
	char left_leg_char = '/';
	switch(get_direction())
	{
		case game_component::direction_type::left:
			left_leg_char = pos_x() % 3 ? '<' : '/';
		break;
	}
	get_game_io()->draw(pos_x(), pos_y(), console::color::blue, true, left_leg_char);
}

void game::game_character::render_right_leg()
{
	char right_leg_char = '\\';
	switch(get_direction())
	{
		case game_component::direction_type::right:
			right_leg_char = pos_x() % 3 ? '>' : '\\';
		break;
	}
	get_game_io()->draw(pos_x() + 2, pos_y(), console::color::blue, true, right_leg_char);
}

bool game::game_character::on_keyboard(int character)
{
	switch(character)
	{
		case -1: // no key pressed
		{
		}
		break;

		case 0x41: // up arrow
		{
			on_jump();
			return true;
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

void game::game_character::on_jump()
{
	if(jump_velocity || !check_game_collision(pos_x(), pos_y() + 1))
		return;

	jump_velocity = get_game_settings()->get_character_jump_velocity();
	log("initialized jump with %d velocity units", jump_velocity);
}

void game::game_character::on_right_arrow()
{
	switch(get_direction())
	{
		case game_component::direction_type::left:
			log("direction is now none");
			set_direction(game_component::direction_type::none);
		return;
		case game_component::direction_type::none:
			log("direction is now right");
			set_direction(game_component::direction_type::right);
		return;
	}

	if(pos_x() >= get_game_settings()->get_game_width() - 20)
	{
		game_map* map = get_game_map();
		map->increment_map_offset();
		return;
	}

	pos_x(pos_x() + 1);
}

void game::game_character::on_left_arrow()
{
	switch(get_direction())
	{
		case game_component::direction_type::right:
			log("direction is now none");
			set_direction(game_component::direction_type::none);
		break;
		case game_component::direction_type::none:
			log("direction is now left");
			set_direction(game_component::direction_type::left);
		break;
	}

	if(check_game_collision(pos_x() - 1, pos_y()))
		return;

	if(pos_x() <= 10 && get_game_map()->get_map_offset())
	{
		get_game_map()->decrement_map_offset();
		return;
	}

	pos_x(pos_x() - 1);

}
