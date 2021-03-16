#include "../common.hpp"
#include "game.hpp"
#include "game_map.hpp"

game::game::game() :
	running(true),
	map(new game_map())
{
}

game::game::~game()
{
	running = false;
	delete map;
}

bool game::game::is_running()
{
	return running;
}


void game::game::tick()
{

}

void game::game::render()
{
	std::cout << console_code::reset_cursor_position << console_code::hide_cursor;
	if(map)
	{
		map->render(0);
	}
}
