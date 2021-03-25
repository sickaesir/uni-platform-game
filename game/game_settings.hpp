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
		bool get_console_mode();
		int get_console_lines();

	private:
		void initialize_settings();
		void parse_cmd_settings(int argc, char** argv);
		bool parse_cmd_arg(char* arg, char* arg_value);

	// settings
	private:
		int game_height;
		int game_width;
		int map_wall_padding;
		int console_lines;
		bool console_mode;
		char* game_path;
	};
}
