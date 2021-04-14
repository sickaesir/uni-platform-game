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
		virtual void render() override;
		virtual game_component* check_collision(game_component* requester, int x, int y) override;

	public:
		virtual unsigned int get_enemy_height() = 0;
		virtual unsigned int get_enemy_width() = 0;
		virtual unsigned int get_laser_y_offset() = 0;
		int get_relative_character_y();
		int get_relative_character_x();
		void add_life(int amount);

	private:
		void render_life();

	protected:
		bool can_shoot();
		void shoot(int x, int y);

	private:
		int relative_character_y;
		int relative_character_x;
		int last_shoot_tick;
		int life;
	};
};
