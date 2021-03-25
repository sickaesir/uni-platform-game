#pragma once
#include "../data/data_vector.hpp"
#include "game_component.hpp"
namespace game
{
	class game : game_component
	{
	public:
		game(int argc, char** argv);
		~game();

	// getters
	public:
		bool is_running();
		class game_map* get_map();

	// public methods
	public:
		virtual void tick() override;
		virtual void render() override;
		virtual bool on_keyboard(int keyboard_key) override;
		void write_log(const char* format, va_list args);

	private:
		void render_console();

	private:
		bool running;
		data::data_vector<class game_component*> components;
		data::data_vector<char*> console_lines;
		class game_map* map;
		class game_input* input;
		class game_settings* settings;
	};
}
