#pragma once
#include "game_component.hpp"
namespace game
{
	class game;
	class game_map : public game_component
	{
	public:
		game_map(game_component* parent, int _game_height, int _game_width, int _wall_padding);
		~game_map();

	// public getters
	public:
		int height();
		int width();

	// public methods
	public:
		virtual void tick() override;
		virtual void render() override;
		virtual bool on_keyboard(int character) override;
		virtual game_component* check_collision(game_component* requester, int x, int y) override;

		int get_map_offset();
		void increment_map_offset();
		void decrement_map_offset();

 	private:
		void extend_map();
		void generate_rock(unsigned int x_offset);

	private:
		char** map_text;
		int map_height;
		int map_width;
		int game_height;
		int game_width;
		int wall_padding;
		int map_offset;
		int rocks_to_generate;
	};
}
