#include "game_character.hpp"

game::game_character::game_character(game_component* parent) : game_component(parent, "game_character"),
	position(0, 0)
{
}

game::game_character::~game_character()
{
}

void game::game_character::tick()
{
}

void game::game_character::render()
{
}

bool game::game_character::on_keyboard(int character)
{
	return false;
}
