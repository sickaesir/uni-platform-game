#include "../common.hpp"
#include "game.hpp"
#include "game_map.hpp"
#include "game_component.hpp"
#include "game_input.hpp"
#include "game_settings.hpp"
#include "game_character.hpp"
#include "../utils/runtime_utils.hpp"

game::game::game(int argc, char** argv) : game_component(nullptr, "game"),
	running(true)
{
	settings = new game_settings(argc, argv); // ! must be first !
	map = new game_map(this, settings->get_game_height(), settings->get_game_width(), settings->get_map_wall_padding());
	input = new game_input(this);
	character = new game_character(this);
	components.add(map);
	components.add(input);
}

game::game::~game()
{
	running = false;
	components.for_each([](int idx, game_component* component) {
		delete component;
	});

	components.resize(0);

	// those gets deleted along with the components
	map = nullptr;
	input = nullptr;
}

bool game::game::is_running()
{
	return running;
}

game::game_map* game::game::get_map()
{
	return map;
}

bool game::game::on_keyboard(int keyboard_key)
{
	for(int i = 0; i < components.get_size(); i++)
		if(components[i] && components[i]->on_keyboard(keyboard_key))
			break;
	return true;
}

void game::game::tick()
{
	components.for_each([](int idx, game_component* component) {
		if(component)
			component->tick();
	});
}

void game::game::render()
{
	printf(console_code::reset_cursor_position);
	components.for_each([](int idx, game_component* component) {
		if(component)
			component->render();
	});

	if(settings->get_console_mode())
		render_console();
}

void game::game::render_console()
{
	for(int i = 0; i < console_lines.get_size(); i++)
		printf(console_lines[i]);
}

void game::game::write_log(const char* format, va_list args)
{
	if(!settings->get_console_mode()) return;
	char buffer[256];
	vsprintf(buffer, format, args);

	int buf_len = utils::runtime_utils::strlen(buffer);
	char* allocation = new char[buf_len + 1];
	utils::runtime_utils::memset_zero(allocation, buf_len + 1);
	utils::runtime_utils::memcpy(allocation, buffer, buf_len);

	console_lines.add(allocation);
	while(console_lines.get_size() > settings->get_console_lines())
	{
		delete[] console_lines[0];
		console_lines.remove_at(0);
	}
}
