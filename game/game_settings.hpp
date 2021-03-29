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
		int get_io_inactive_ticks();
		int get_character_jump_velocity();
		int get_gravity_ticks();
		int get_map_offsetting_min();
		int get_map_offsetting_max();
		int get_map_offset_threshold();

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
		int io_inactive_ticks;
		int character_jump_velocity;
		bool console_mode;
		int gravity_ticks;
		int map_offsetting_min;
		int map_offsetting_max;
		int map_offset_threshold;
		char* game_path;
	};
}
