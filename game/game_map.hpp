#pragma once
#include "game_component.hpp"
namespace game
{
	class game_map : public game_component
	{
	public:
		game_map();
		~game_map();

	// public getters
	public:
		int height();
		int width();

	// public methods
	public:
		virtual void tick() override;
		virtual void render() override;

 	private:
		void extend_map();

	private:
		char** map_text;
		int map_height;
		int map_width;
	};
}
