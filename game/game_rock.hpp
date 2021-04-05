#pragma once
#include "game_component.hpp"

namespace game
{
	class game_rock : public game_component
	{
	public:
		game_rock(game_component* parent, int rock_index);
		~game_rock();

	public:
		virtual void render() override;

		int get_rock_height();
		int get_rock_width();

	private:
		void parse_rock_by_index(int rock_index);

	private:
		int rock_height;
		int rock_width;
		char** rock_text;
	};
};
