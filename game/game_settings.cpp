#include "game_settings.hpp"
#include "../common.hpp"
#include "../utils/runtime_utils.hpp"

game::game_settings::game_settings(int argc, char** argv)
{
	initialize_settings();
	parse_cmd_settings(argc, argv);
}

void game::game_settings::initialize_settings()
{
	game_height = settings::game_height;
	game_width = settings::game_width;
	map_wall_padding = settings::map_wall_padding;
}

void game::game_settings::parse_cmd_settings(int argc, char** argv)
{
	game_path = argv[0];

	for(int i = 1; i < argc; i++)
	{
		std::cout << argv[i] << std::endl;
		int arg_len = utils::runtime_utils::strlen(argv[i]);
	}

}

int game::game_settings::get_game_height()
{
	return game_height;
}

int game::game_settings::get_game_width()
{
	return game_width;
}
