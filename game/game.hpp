#pragma once
#include "../data/data_vector.hpp"
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

	private:
		bool running;
		data::data_vector<game_component*>* components;
	};
}
