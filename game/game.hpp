#pragma once
#include "../data/data_vector.hpp"
#include "game_component.hpp"
namespace game
{
	class game : game_component
	{
	public:
		game();
		~game();

	// getters
	public:
		bool is_running();

	// public methods
	public:
		virtual void tick() override;
		virtual void render() override;
		virtual bool on_keyboard(int keyboard_key) override;

	private:
		bool running;
		data::data_vector<class game_component*> components;
		class game_map* map;
		class game_input* input;
	};
}
