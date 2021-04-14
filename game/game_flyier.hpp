#pragma once
#include "game_enemy.hpp"
namespace game
{
	class game_flyier : public game_enemy
	{
	public:
		game_flyier(game_component* parent);

	public:
		virtual void tick() override;
		virtual void render() override;
		virtual unsigned int get_enemy_height() override;
		virtual unsigned int get_enemy_width() override;
		virtual unsigned int get_laser_y_offset() override;

	private:
		void shoot_tick();
		void move_tick();
	};
};
