#include "game_enemy.hpp"
#include "game_character.hpp"
#include "game.hpp"
#include "game_trooper.hpp"
#include "game_map.hpp"
#include "game_settings.hpp"
#include "game_laser.hpp"
#include "game_io.hpp"

game::game_enemy::game_enemy(game_component* parent, game_component::component_type type) :
	game_component(parent, type),
	last_shoot_tick(0),
	life(get_game_settings()->get_enemy_base_life())
{

}

void game::game_enemy::tick()
{
	int character_x = get_game_character()->pos_x() + get_game_map()->get_map_offset();
	int character_y = get_game_character()->pos_y() - 3;
	int x = pos_x();


	if(x > character_x)
		set_direction(game_component::direction_type::left);
	else if(x < character_x)
		set_direction(game_component::direction_type::right);


	if(x > character_x + get_game_settings()->get_enemy_character_distance())
		relative_character_x = -1;
	else if(x < character_x - get_game_settings()->get_enemy_character_distance())
		relative_character_x = 1;
	else
		relative_character_x = 0;


	int enemy_top = pos_y() - get_enemy_height();

	if(enemy_top > character_y)
		relative_character_y = -1;
	else if(enemy_top < character_y)
		relative_character_y = 1;
	else
		relative_character_y = 0;

	game_component::tick();
}

void game::game_enemy::render()
{
	render_life();

	game_component::render();
}

void game::game_enemy::render_life()
{
	float life_percentage = life / (float)get_game_settings()->get_enemy_base_life();
	int bars_to_render = (life_percentage * 25.0f) / 7;

	console::color bar_color = console::color::cyan;
	switch(bars_to_render)
	{
		case 2: bar_color = console::color::green; break;
		case 1: bar_color = console::color::yellow; break;
		case 0: bar_color = console::color::red; break;
	}

	int base_x = pos_x() - get_game_map()->get_map_offset();
	if(base_x < 0 || base_x > get_game_settings()->get_game_width())
		return;

	get_game_io()->draw(base_x + 1, pos_y() - get_enemy_height() - 1, bar_color, true, '=');
	for(int i = 0; i < bars_to_render; i++)
	{
		get_game_io()->draw(base_x - i, pos_y() - get_enemy_height() - 1, bar_color, true, '=');
		get_game_io()->draw(base_x + 2 + i, pos_y() - get_enemy_height() - 1, bar_color, true, '=');
	}
}

bool game::game_enemy::can_shoot()
{
	return get_tick_count() - last_shoot_tick >= get_game_settings()->get_enemy_shoot_tick_interval() && relative_character_y == 0;
}

void game::game_enemy::shoot(game_laser* laser)
{
	if(!can_shoot())
	{
		delete laser;
		return;
	}

	laser->set_direction(get_direction());
	add_component(laser);

	last_shoot_tick = get_tick_count();
}

game::game_enemy* game::game_enemy::generate_enemy(game_component::component_type enemy_type, game_component* parent)
{
	switch(enemy_type)
	{
		case game_component::component_type::trooper:
			return new game_trooper(parent);
		default:
			return nullptr;
	}
}

int game::game_enemy::get_relative_character_y()
{
	return relative_character_y;
}

int game::game_enemy::get_relative_character_x()
{
	return relative_character_x;
}

game::game_component* game::game_enemy::check_collision(game_component* requester, int x, int y)
{
	int render_x = pos_x() - get_game_map()->get_map_offset();
	for(int rx = render_x - 1; rx < render_x + get_enemy_width() + 1; rx++)
	{
		if(rx < 0 || rx > get_game_settings()->get_game_width())
			continue;

		for(int ry = pos_y() - get_enemy_height() + 1; ry < pos_y(); ry++)
		{
			if(ry == y && x == rx)
				return this;
		}
	}

	return game_component::check_collision(requester, x, y);
}
