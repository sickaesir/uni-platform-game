#pragma once
#include "game_component.hpp"
#include "../data/data_point.hpp"

namespace game
{
	class game_character : public game_component
	{
	public:
		game_character(game_component* parent);
		~game_character();

	public:
		virtual void tick() override;
		virtual void render() override;
		virtual bool on_keyboard(int character) override;
		virtual game_component* check_collision(game_component* requester, int x, int y) override;

	public:
		void add_life(int amount);
		void upgrade_laser();
		void upgrade_jump();
		int get_using_laser();
		int get_extra_jump();
		int get_life();
		void initialize_position();

	private:
		void render_head();
		void render_body();
		void render_left_arm();
		void render_right_arm();
		void render_left_leg();
		void render_right_leg();
		void render_life();

	private:
		void on_right_arrow();
		void on_left_arrow();
		void on_jump();
		void on_shoot();

	private:
		bool check_character_collision(int x, int y);
		void jump_tick();

	private:
		int jump_velocity;
		int life;
		int last_shoot_tick;
		int using_laser;
		int extra_jump;
	};
}
