#pragma once
#include "../data/data_vector.hpp"
#include "../data/data_point.hpp"

namespace game
{
	class game_component
	{
	// component types
	public:
		enum class direction_type
		{
			right,
			none,
			left
		};


	public:
		game_component(game_component* parent, const char* name);
	public:
		virtual void render();
		virtual void tick();
		virtual bool on_keyboard(int character);
		virtual bool check_collision(game_component* requester, int x, int y);
		void log(const char* format, ...);

	public:
		void add_component(game_component* component);
		game_component* get_parent();
		class game_map* get_game_map();
		class game* get_game_instance();
		class game_settings* get_game_settings();
		class game_io* get_game_io();
		bool check_game_collision(int x, int y);
		int get_children_count();
		game_component* get_child(int index);
		unsigned int get_tick_count();

	public:
		int pos_x();
		int pos_y();
		void pos_x(int x);
		void pos_y(int y);

		direction_type get_direction();
		void set_direction(direction_type dir);

	private:
		game_component* parent_component;
		const char* component_name;
		data::data_vector<game_component*> children;
		data::data_point position;
		direction_type direction;
	};
}
