#pragma once
#include "game_enemy.hpp"
namespace game
{
	class game_trooper : public game_enemy
	{
	public:
		game_trooper(game_component* parent);

	public:
		virtual void tick() override;
		virtual void render() override;

	public:
		virtual unsigned int get_enemy_height() override;
		virtual unsigned int get_enemy_width() override;
	};
};
