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
		virtual bool check_collision(game_component* requester, int x, int y) override;

 	private:
		void extend_map();

	private:
		char** map_text;
		int map_height;
		int map_width;
		int game_height;
		int game_width;
		int wall_padding;
	};
}
