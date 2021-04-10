#include "game_enemy.hpp"
#include "game_character.hpp"
#include "game.hpp"
#include "game_trooper.hpp"
#include "game_map.hpp"

game::game_enemy::game_enemy(game_component* parent, game_component::component_type type) :
	game_component(parent, type)
{

}

void game::game_enemy::tick()
{
	int character_x = get_game_character()->pos_x() + get_game_map()->get_map_offset();
	int character_y = get_game_character()->pos_y() - get_game_map()->get_map_offset();
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
