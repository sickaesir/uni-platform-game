#include "../common.hpp"
#include "game.hpp"
#include "game_map.hpp"
#include "game_component.hpp"
#include "game_io.hpp"
#include "game_settings.hpp"
#include "game_character.hpp"
#include "../utils/runtime_utils.hpp"

game::game::game(int argc, char** argv) : game_component(nullptr, "game"),
	running(true)
{
	settings = new game_settings(argc, argv); // ! must be first !
	map = new game_map(this, settings->get_game_height(), settings->get_game_width(), settings->get_map_wall_padding());
	io = new game_io(this);
	character = new game_character(this);
	add_component(map);
	add_component(io);
	add_component(character);
}

game::game::~game()
{
	running = false;

	// those gets deleted along with the components
	map = nullptr;
	io = nullptr;
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
	return game::game_component::on_keyboard(keyboard_key);
}

void game::game::tick()
{
	game::game_component::tick();
}

void game::game::render()
{
	io->clear_screen();
	game::game_component::render();
	if(settings->get_console_mode())
		render_console();
}

void game::game::render_console()
{
	move(settings->get_game_height(), 0);
	for(int i = 0; i < console_lines.get_size(); i++)
	{
		io->draw(3, settings->get_game_height() + i, console::color::yellow, false, console_lines[i]);
		//printw(console_lines[i]);
	}
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

game::game_settings* game::game::get_settings()
{
	return settings;
}

game::game_io* game::game::get_io()
{
	return io;
}
