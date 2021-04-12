#pragma once
#include "game_component.hpp"

namespace game
{
	class game_laser : public game_component
	{
	public:
		game_laser(game_component* parent, int laser_type,
			console::color laser_color = console::color::red,
			bool skip_rock_collision = false);
		~game_laser();

	public:
		virtual void tick() override;
		virtual void render() override;
		int get_laser_length();

	private:
		int get_laser_index();
		void check_laser_collision();

	private:
		console::color color;
		bool skip_rock;
		int type;
		data::data_point collision_point;
		bool collided;
	};
};
