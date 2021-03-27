#pragma once
#include "../data/data_vector.hpp"
#include "game_component.hpp"
namespace game
{
	class game : public game_component
	{
	public:
		game(int argc, char** argv);
		~game();

	// getters
	public:
		bool is_running();
		class game_map* get_map();
		class game_settings* get_settings();
		class game_io* get_io();

	// public methods
	public:
		virtual void tick() override;
		virtual void render() override;
		virtual bool on_keyboard(int keyboard_key) override;
		void write_log(const char* format, va_list args);
		unsigned int get_tick_count();

	private:
		void render_console();

	private:
		bool running;
		data::data_vector<char*> console_lines;
		class game_map* map;
		class game_io* io;
		class game_settings* settings;
		class game_character* character;
		unsigned int tick_count;
	};
}
