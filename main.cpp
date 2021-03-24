#include "common.hpp"
#include "game/game.hpp"
#include "data/data_map.hpp"

int main(int argc, char** argv)
{
	game::game* main_game = new game::game(argc, argv);
	return 0;

	while(main_game->is_running())
	{
		main_game->tick();
		main_game->render();
	}

	delete main_game;
	main_game = nullptr;

	return 0;
}
