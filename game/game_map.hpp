#pragma once
#include "game_component.hpp"
namespace game
{
	class game;
	class game_map : public game_component
	{
	public:
		game_map(game_component* parent);
		~game_map();

	// public methods
	public:
		virtual void tick() override;
		virtual void render() override;
		virtual bool on_keyboard(int character) override;
		virtual game_component* check_collision(game_component* requester, int x, int y) override;

		int get_map_offset();
		void increment_map_offset();
		void decrement_map_offset();
		void reset_map_offset();

 	private:
		void extend_map();
		void generate_rocks();
		void generate_powerups();
		void generate_enemies();
	private:
		int map_offset;
		int rocks_to_generate;
		int powerups_to_generate;
		int enemies_to_generate;
	};
}
