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

		enum class component_type : unsigned int
		{
			game,
			character,
			io,
			laser,
			map,
			rock,
			powerup,
			menu,

			// enemies
			trooper,
			flyier
		};

		static constexpr const component_type enemy_start = component_type::trooper;
		static constexpr const component_type enemy_end = component_type::flyier;


	public:
		game_component(game_component* parent, component_type _type);
	public:
		virtual void render();
		virtual void tick();
		virtual bool on_keyboard(int character);
		virtual game_component* check_collision(game_component* requester, int x, int y);
		void log(const char* format, ...);

	public:
		void add_component(game_component* component);
		void remove_component(game_component* component);
		void invalidate();
		bool is_enemy();
		game_component* get_parent();
		class game_map* get_game_map();
		class game* get_game_instance();
		class game_settings* get_game_settings();
		class game_io* get_game_io();
		class game_character* get_game_character();
		game_component* check_game_collision(int x, int y);
		int get_children_count();
		game_component* get_child(int index);
		unsigned int get_tick_count();
		component_type get_type();
		const char* get_type_str();
		void clear_children();

	public:
		int pos_x();
		int pos_y();
		void pos_x(int x);
		void pos_y(int y);

		direction_type get_direction();
		void set_direction(direction_type dir);

	private:
		game_component* parent_component;
		data::data_vector<game_component*> children;
		data::data_vector<game_component*> invalidated_children;
		data::data_point position;
		direction_type direction;
		component_type type;
	};
}
