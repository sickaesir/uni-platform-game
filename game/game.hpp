#pragma once
#include "../data/data_vector.hpp"
#include "game_input.hpp"
namespace game
{
	class game_component;
	class game
	{
	public:
		game();
		~game();

	// getters
	public:
		bool is_running();

	// public methods
	public:
		void tick();
		void render();

	// private methods
	private:
		void on_keyboard_input(int keyboard_key);

	private:
		bool running;
		data::data_vector<game_component*>* components;
		class game_map* map;
		game_input<game>* input;
	};
}
