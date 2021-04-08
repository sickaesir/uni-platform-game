#include "../common.hpp"
#include "game.hpp"
#include "game_map.hpp"
#include "game_component.hpp"
#include "game_io.hpp"
#include "game_settings.hpp"
#include "game_character.hpp"
#include "../utils/runtime_utils.hpp"
#include "../utils/memory_utils.hpp"

game::game::game(int argc, char** argv) : game_component(nullptr, game_component::component_type::game),
	running(true),
	tick_count(0)
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
	tick_count++;
	if(tick_count == 0)
	{
		tick_count = 1;
		log("tick count overflow, next tick is 1");
	}

	game::game_component::tick();
}

unsigned int game::game::get_tick_count()
{
	return tick_count;
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
	for(int i = 0; i < console_lines.get_size(); i++)
		io->draw(3, settings->get_game_height() + i, console::color::yellow, false, console_lines[i]);
}

void game::game::write_log(const char* format, va_list args)
{
	if(!settings->get_console_mode()) return;
	char buffer[256];
	vsprintf(buffer, format, args);

	int buf_len = utils::runtime_utils::strlen(buffer);
	char* allocation = new char[buf_len + 1];
	utils::memory_utils::memory_set_zero(allocation, buf_len + 1);
	utils::memory_utils::memory_copy(allocation, buffer, buf_len);

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

unsigned int game::game::urandom_number()
{
	int* entropy = new int;
	unsigned int random = *entropy ^ utils::memory_utils::djb2_hash(get_tick_count());
	delete entropy;
	return random;
}

unsigned int game::game::urandom_number(unsigned int min, unsigned int max)
{
	return min + (urandom_number() % (max - min + 1));
}
