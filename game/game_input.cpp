#include "../common.hpp"
#include "game_input.hpp"
#include <ncurses.h>

game::game_input::game_input(game_component* parent) : game_component(parent)
{

}

game::game_input::~game_input()
{

}

void game::game_input::tick()
{
	int current_char = getch();
	game_component* parent = get_parent();
	if(current_char && parent)
		parent->on_keyboard(current_char);
}

void game::game_input::render()
{

}


bool game::game_input::on_keyboard(int character)
{
	return false;
}
