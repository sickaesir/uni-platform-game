#include "game_component.hpp"

game::game_component::game_component(game_component* parent) :
	parent_component(parent)
{
}

game::game_component* game::game_component::get_parent()
{
	return parent_component;
}
