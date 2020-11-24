#include "common.hpp"
#include "game/game.hpp"
#include "data/data_map.hpp"

int main(int argc, char** argv)
{
	data::data_map<int, int> map;

	map.set(0, 15);
	map.set(15, 48);

	std::cout << map.has_key(0) << std::endl;


	game::game* main_game = new game::game();

	while(main_game->is_running())
	{
		main_game->tick();
	}

	delete main_game;
	main_game = nullptr;

	return 0;
}
