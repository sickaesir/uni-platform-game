#include "game_menu.hpp"
#include "game_settings.hpp"
#include "game_io.hpp"
#include "game_character.hpp"
#include "game.hpp"

game::game_menu::game_menu(game_component* parent) : game_component(parent, game_component::component_type::menu)
{

}

void game::game_menu::render()
{
	int character_life = get_game_character()->get_life();
	int max_character_life = get_game_settings()->get_max_character_life();
	int points = get_game_instance()->get_points();
	int character_laser = get_game_character()->get_using_laser();
	int max_laser = sprites::lasers_count;
	int character_jump = get_game_character()->get_extra_jump();
	int character_max_jump = get_game_settings()->get_powerup_max_total_jump();


	for(int i = 0; i < get_game_settings()->get_game_height() + 1; i++)
		get_game_io()->draw(get_game_settings()->get_game_width() + 2, i, console::color::magenta, true, '#');

	int render_x = get_game_settings()->get_game_width() + 4;
	int render_y = 3;
	get_game_io()->draw(render_x, render_y, console::color::cyan, true, "- life: %d / %d", character_life, max_character_life);
	render_y += 2;
	get_game_io()->draw(render_x, render_y, console::color::cyan, true, "- points: %d", points);
	render_y += 2;
	get_game_io()->draw(render_x, render_y, console::color::cyan, true, "- laser: ");
	for(int i = 0; i < max_laser; i++)
		get_game_io()->draw(render_x + 9 + i, render_y, console::color::green, true, i <= character_laser ? '#' : '-');
	render_y += 2;

	get_game_io()->draw(render_x, render_y, console::color::cyan, true, "- jump: ");
	for(int i = 0; i < character_max_jump; i++)
		get_game_io()->draw(render_x + 8 + i, render_y, console::color::green, true, i <= character_jump ? '#' : '-');



}
