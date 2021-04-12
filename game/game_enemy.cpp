#include "game_enemy.hpp"
#include "game_character.hpp"
#include "game.hpp"
#include "game_trooper.hpp"
#include "game_map.hpp"
#include "game_settings.hpp"

game::game_enemy::game_enemy(game_component* parent, game_component::component_type type) :
	game_component(parent, type)
{

}

void game::game_enemy::tick()
{
	int character_x = get_game_character()->pos_x() + get_game_map()->get_map_offset();
	int character_y = get_game_character()->pos_y() + get_game_map()->get_map_offset();
	int x = pos_x();

	log("cx:%d x:%d", character_x, x);

	if(x > character_x)
		relative_character_x = -1;
	else if(x < character_x)
		relative_character_x = 1;
	else
		relative_character_x = 0;

	if(pos_y() > character_y)
		relative_character_y = -1;
	else if(pos_y() < character_y)
		relative_character_y = 1;
	else
		relative_character_x = 0;
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
