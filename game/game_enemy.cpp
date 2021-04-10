#include "game_enemy.hpp"
#include "game_character.hpp"
#include "game.hpp"
#include "game_trooper.hpp"

game::game_enemy::game_enemy(game_component* parent, game_component::component_type type) :
	game_component(parent, type)
{

}

void game::game_enemy::tick()
{
	int character_x = get_game_character()->pos_x();
	int character_y = get_game_character()->pos_y();

	if(pos_x() > character_x)
		relative_character_x = character_x - pos_x();
	else if(pos_x() < character_y)
		relative_character_x = pos_x() - character_x;
	else
		relative_character_x = 0;

	if(pos_y() > character_y)
		relative_character_y = character_y - pos_y();
	else if(pos_y() < character_y)
		relative_character_y = pos_y() - character_y;
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

