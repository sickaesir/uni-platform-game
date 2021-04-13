#include "../common.hpp"
#include "game.hpp"
#include "game_map.hpp"
#include "../utils/memory_utils.hpp"
#include "game_io.hpp"
#include "../utils/runtime_utils.hpp"
#include "game_settings.hpp"
#include "game_rock.hpp"
#include "game_powerup.hpp"
#include "game_enemy.hpp"
#include "game_character.hpp"

game::game_map::game_map(game_component* parent) :
	game_component(parent, game_component::component_type::map),
	map_offset(0),
	rocks_to_generate(0),
	powerups_to_generate(0),
	enemies_to_generate(0)
{
}

game::game_map::~game_map()
{
}

void game::game_map::extend_map()
{
	rocks_to_generate += get_game_settings()->get_rocks_gen_count();
	powerups_to_generate += get_game_settings()->get_powerup_max_gen_amount();
	enemies_to_generate += get_game_settings()->get_enemy_gen_count() + get_game_character()->get_extra_jump() + get_game_character()->get_using_laser();
}


void game::game_map::generate_powerups()
{
	if(!powerups_to_generate)
		return;

	unsigned int x_offset = get_game_settings()->get_game_width() + map_offset;
	game_powerup::powerup_type type = static_cast<game_powerup::powerup_type>(get_game_instance()->urandom_number(0, static_cast<unsigned int>(game_powerup::powerup_type::_last) - 1));
	int x = get_game_instance()->urandom_number(x_offset + get_game_settings()->get_map_wall_padding(), x_offset + get_game_settings()->get_game_width() - 5);
	int y = get_game_settings()->get_map_wall_padding() + 5;

	game_powerup* powerup = new game_powerup(this, type);
	powerup->pos_x(x);
	powerup->pos_y(y);

	for(int rx = -5; rx < 5; rx++)
	{
		for(int ry = -5; ry < 5; ry++)
		{
			if(get_game_instance()->check_collision(powerup, x + rx, y + ry))
			{
				delete powerup;
				return;
			}
		}
	}

	add_component(powerup);
	powerups_to_generate--;
}

void game::game_map::generate_enemies()
{
	if(!enemies_to_generate)
		return;

	unsigned int x_offset = get_game_settings()->get_game_width() + map_offset;
	game_component::component_type enemy_type =
			(game_component::component_type)get_game_instance()->urandom_number((unsigned int)game_component::enemy_start,
											(unsigned int)game_component::enemy_end);
	game_enemy* enemy = game_enemy::generate_enemy(enemy_type, this);

	int x = get_game_instance()->urandom_number(x_offset + get_game_settings()->get_map_wall_padding(),
							x_offset + get_game_settings()->get_game_width() - enemy->get_enemy_width());
	int y = get_game_instance()->urandom_number(get_game_settings()->get_map_wall_padding(),
		get_game_settings()->get_game_height() - get_game_settings()->get_map_wall_padding() - enemy->get_enemy_height());

	enemy->pos_x(x);
	enemy->pos_y(y);

	for(int rx = -enemy->get_enemy_width(); rx < enemy->get_enemy_width(); rx++)
	{
		for(int ry = -enemy->get_enemy_height(); ry < enemy->get_enemy_height(); ry++)
		{
			if(check_collision(enemy, x + rx - map_offset, y + ry))
			{
				delete enemy;
				return;
			}
		}
	}

	add_component(enemy);
	enemies_to_generate--;
}

void game::game_map::generate_rocks()
{
	if(!rocks_to_generate)
		return;

	unsigned int x_offset = get_game_settings()->get_game_width() + map_offset;

	int rock_index = get_game_instance()->urandom_number(0, sprites::rocks_count - 1);
	game_rock* rock = new game_rock(this, rock_index);

	int x = get_game_instance()->urandom_number(x_offset + get_game_settings()->get_map_wall_padding()
				, x_offset + get_game_settings()->get_game_width() - rock->get_rock_width());
	int y = get_game_instance()->urandom_number(get_game_settings()->get_map_wall_padding(),
				get_game_settings()->get_game_height() - get_game_settings()->get_map_wall_padding() - rock->get_rock_height());
	rock->pos_x(x);
	rock->pos_y(y);

	int padding = get_game_settings()->get_rock_gen_collision_padding();
	for(int rx = -padding; rx < rock->get_rock_width() + padding; rx++)
	{
		for(int ry = -padding; ry < rock->get_rock_height() + padding; ry++)
		{
			if(check_collision(rock, x + rx - map_offset, y + ry))
			{
				delete rock;
				return;
			}
		}

	}

	add_component(rock);
	rocks_to_generate--;
}

game::game_component* game::game_map::check_collision(game_component* requester, int x, int y)
{
	if(x < get_game_settings()->get_map_wall_padding() - map_offset || y < get_game_settings()->get_map_wall_padding())
	{
		//log("sm %d %d %d %d", x, get_game_settings()->get_map_wall_padding(), map_offset, get_game_settings()->get_map_wall_padding() - map_offset);
		return this;
	}

	if(y > get_game_settings()->get_game_height() - get_game_settings()->get_map_wall_padding())
		return this;

	return game_component::check_collision(requester, x, y);
}

void game::game_map::render()
{
	for(int y = 0; y < get_game_settings()->get_game_height(); y++)
		for(int x = 0; x < get_game_settings()->get_map_wall_padding() - map_offset; x++)
			get_game_io()->draw(x, y, console::color::magenta, false, '|');

	int map_ground_sprite_len = utils::runtime_utils::strlen((char*)sprites::map_ground_pattern);
	for(int y = 0; y < get_game_settings()->get_map_wall_padding(); y++)
	{
		for(int x = 0; x < get_game_settings()->get_game_width(); x++)
		{
			console::color color = (x + map_offset) % 4 ? console::color::magenta : console::color::cyan;
			get_game_io()->draw(x, y, color, false, sprites::map_ground_pattern[(x + map_offset) % map_ground_sprite_len]);
			get_game_io()->draw(x, get_game_settings()->get_game_height() - y, color, false, sprites::map_ground_pattern[(x + map_offset) % map_ground_sprite_len]);
		}
	}

	game_component::render();
}

void game::game_map::tick()
{
	generate_rocks();
	generate_powerups();
	generate_enemies();
	game_component::tick();
}

bool game::game_map::on_keyboard(int character)
{
	return false;
}

void game::game_map::increment_map_offset()
{
	map_offset++;
	if(!(map_offset % get_game_settings()->get_map_offset_threshold()))
	{
		extend_map();
	}
}

void game::game_map::decrement_map_offset()
{
	map_offset--;
}

void game::game_map::reset_map_offset()
{
	map_offset = 0;
}

int game::game_map::get_map_offset()
{
	return map_offset;
}
