#include "game_character.hpp"
#include "../utils/runtime_utils.hpp"
#include "game_settings.hpp"
#include "game_io.hpp"
#include "game_map.hpp"
#include "game_laser.hpp"
#include "game.hpp"
#include "game_powerup.hpp"

game::game_character::game_character(game_component* parent) : game_component(parent, game_component::component_type::character)
	, jump_velocity(0)
	, life(get_game_settings()->get_max_character_life())
	, last_shoot_tick(0)
	, using_laser(0)
	, extra_jump(0)
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
	game_component::tick();
}

void game::game_character::jump_tick()
{
	if(get_tick_count() % get_game_settings()->get_gravity_ticks())
		return;

	if(!jump_velocity)
	{
		for(int i = 0; i < 3; i++)
			if(check_character_collision(pos_x() + i, pos_y() + 1))
				return;
		switch(get_direction())
		{
			case game_component::direction_type::right:
				on_right_arrow();
			break;
			case game_component::direction_type::left:
				on_left_arrow();
			break;
		}

		pos_y(pos_y() + 1);
		return;
	}

	for(int i = 0; i < 3; i++)
	{
		if(check_character_collision(pos_x() + i, pos_y() - 3))
		{
			log("found collision at next y(%d), jump aborted", pos_y() - 1);
			jump_velocity = 0;
			return;
		}
	}

	jump_velocity--;

	switch(get_direction())
	{
		case game_component::direction_type::right:
			on_right_arrow();
		break;
		case game_component::direction_type::left:
			on_left_arrow();
		break;
	}

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

bool game::game_character::check_character_collision(int x, int y)
{
	game_component* collision_component = check_game_collision(x, y);

	if(!collision_component)
		return false;

	if(collision_component->get_type() == game_component::component_type::powerup)
	{
		game_powerup* powerup = reinterpret_cast<game_powerup*>(collision_component);
		log("detected powerup pickup, type: %d", powerup->get_type());
		powerup->pick();
	}

	return true;
}

void game::game_character::render()
{
	render_head();
	render_body();
	render_left_arm();
	render_right_arm();
	render_left_leg();
	render_right_leg();
	render_life();

	game_component::render();
}

void game::game_character::render_life()
{
	float character_life_percentage = life / (float)get_game_settings()->get_max_character_life();
	int bars_to_render = (character_life_percentage * 25.0f / 7);

	console::color bar_color = console::color::cyan;
	switch(bars_to_render)
	{
		case 2: bar_color = console::color::green; break;
		case 1: bar_color = console::color::yellow; break;
		case 0: bar_color = console::color::red; break;
	}

	get_game_io()->draw(pos_x() + 1, pos_y() - 3, bar_color, true, '=');

	for(int i = 0; i < bars_to_render; i++)
	{
		get_game_io()->draw(pos_x() - i, pos_y() - 3, bar_color, true, '=');
		get_game_io()->draw(pos_x() + 2 + i, pos_y() - 3, bar_color, true, '=');
	}
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
	int map_offset = get_game_map()->get_map_offset();
	switch(get_direction())
	{
		case game_component::direction_type::right:
			left_arm_char = (pos_x() + map_offset) % 4 ? '/' : '<';
		break;
		case game_component::direction_type::left:
			left_arm_char = (pos_x() + map_offset) % 4 ? '\'' : '-';
	}

	get_game_io()->draw(pos_x(), pos_y() - 1, console::color::blue, true, left_arm_char);
}

void game::game_character::render_right_arm()
{
	char right_arm_char = '>';
	int map_offset = get_game_map()->get_map_offset();
	switch(get_direction())
	{
		case game_component::direction_type::right:
			right_arm_char = (pos_x() + map_offset) % 4 ? '\'' : '-';
		break;
		case game_component::direction_type::left:
			right_arm_char = (pos_x() + map_offset) % 4 ? '\\' : '>';
		break;
	}

	get_game_io()->draw(pos_x() + 2, pos_y() - 1, console::color::blue, true, right_arm_char);
}

void game::game_character::render_left_leg()
{
	char left_leg_char = '/';
	int map_offset = get_game_map()->get_map_offset();
	switch(get_direction())
	{
		case game_component::direction_type::left:
			left_leg_char = (pos_x() + map_offset) % 3 ? '<' : '/';
		break;
	}
	get_game_io()->draw(pos_x(), pos_y(), console::color::blue, true, left_leg_char);
}

void game::game_character::render_right_leg()
{
	char right_leg_char = '\\';
	int map_offset = get_game_map()->get_map_offset();
	switch(get_direction())
	{
		case game_component::direction_type::right:
			right_leg_char = (pos_x() + map_offset) % 3 ? '>' : '\\';
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

		case 0x20:
		{
			on_shoot();
			return true;
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
	if(jump_velocity)
		return;

	bool can_jump = false;
	for(int i = 0; i < 3; i++)
		if(check_character_collision(pos_x() + i, pos_y() + 1))
			can_jump = true;

	if(!can_jump)
	{
		log("no foot collision, skipping jump");
		return;
	}

	jump_velocity = get_game_settings()->get_character_jump_velocity() + extra_jump;
	log("initialized jump with %d velocity units", jump_velocity);
}

void game::game_character::on_right_arrow()
{
	switch(get_direction())
	{
		case game_component::direction_type::left:
			log("direction is now none");
			set_direction(game_component::direction_type::none);
		break;
		case game_component::direction_type::none:
			log("direction is now right");
			set_direction(game_component::direction_type::right);
		break;
	}

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 3; j++)
			if(check_character_collision(pos_x() + i, pos_y() - j))
				return;

	if(pos_x() >= get_game_settings()->get_game_width() - get_game_settings()->get_map_offsetting_max())
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

	for(int i = -1; i < 2; i++)
		for(int j = 0; j < 3; j++)
		if(check_character_collision(pos_x() + i, pos_y() - j))
			return;

	if(pos_x() <= get_game_settings()->get_map_offsetting_min() && get_game_map()->get_map_offset())
	{
		get_game_map()->decrement_map_offset();
		return;
	}

	pos_x(pos_x() - 1);

}

void game::game_character::on_shoot()
{
	if(get_game_instance()->get_tick_count() - last_shoot_tick < get_game_settings()->get_character_reattack_ticks())
		return;

	last_shoot_tick = get_game_instance()->get_tick_count();

	log("created laser");
	game_laser* laser = new game_laser(this, using_laser);
	laser->pos_y(pos_y() - 1);
	laser->set_direction(get_direction());

	if(get_direction() == game_component::direction_type::left)
		laser->pos_x(pos_x() - laser->get_laser_length());
	else
		laser->pos_x(pos_x() + 2);
	add_component(laser);
}

void game::game_character::add_life(int amount)
{
	life += amount;

	if(life > get_game_settings()->get_max_character_life())
		life = get_game_settings()->get_max_character_life();

	if(life < 0)
		life = 0;
}

void game::game_character::upgrade_laser()
{
	if(using_laser == sprites::lasers_count - 1)
		return;

	using_laser++;
}

void game::game_character::upgrade_jump()
{
	if(extra_jump == get_game_settings()->get_powerup_max_total_jump())
		return;

	extra_jump++;
}

int game::game_character::get_using_laser()
{
	return using_laser;
}

int game::game_character::get_extra_jump()
{
	return extra_jump;
}

game::game_component* game::game_character::check_collision(game_component* requester, int x, int y)
{
	int render_x = pos_x() /*- get_game_map()->get_map_offset()*/;

	for(int rx = render_x; rx < render_x + 3; rx++)
	{
		for(int ry = pos_y() - 3; ry < pos_y(); ry++)
		{
			if(rx == x && ry == y)
				return this;
		}
	}

	return game_component::check_collision(requester, x, y);
}
