#include "../common.hpp"
#include "game_input.hpp"
#include <ncurses.h>


game::game_input::game_input(game_component* parent) : game_component(parent, "game_input")
{
	raw();
	initscr();
	nocbreak();
	nodelay(stdscr, true);
	noecho();
	curs_set(0);
//	setvbuf(stdout, NULL, _IOLBF, 0);
//	setvbuf(stderr, NULL, _IONBF, 0);

}

game::game_input::~game_input()
{

}

void game::game_input::tick()
{
	int current_char = getch();
	if(current_char == -1) return;

	log("received keyboard input -> 0x%04x", current_char);
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
