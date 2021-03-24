#pragma once

namespace game
{
	class game_settings
	{
	public:
		game_settings(int argc, char** argv);

	// getters
	public:
		int get_game_height();
		int get_game_width();
		int get_map_wall_padding();

	private:
		void initialize_settings();
		void parse_cmd_settings(int argc, char** argv);

	// settings
	private:
		int game_height;
		int game_width;
		int map_wall_padding;
		char* game_path;
	};
}
