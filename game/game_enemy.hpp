#pragma once
#include "game_component.hpp"

namespace game
{
	class game_enemy : public game_component
	{
	public:
		game_enemy(game_component* parent, game_component::component_type type);

	public:
		static game_enemy* generate_enemy(game_component::component_type enemy_type, game_component* parent);

	public:
		virtual void tick() override;

	public:
		virtual unsigned int get_enemy_height() = 0;
		virtual unsigned int get_enemy_width() = 0;

	private:
		int relative_character_y;
		int relative_character_x;
	};
};
