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

	private:
		void on_right_arrow();
		void on_left_arrow();

	private:
		void initialize_position();
	};
}
