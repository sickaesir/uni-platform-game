#include "../common.hpp"
#include "game.hpp"
#include "game_map.hpp"
#include "game_component.hpp"
//#include "game_input.hpp"
#include "game_input.cpp"

game::game::game() :
	running(true)
{
	map = new game_map();
	input = new game_input<game>();
	input->set_input_callback(&game::game::on_keyboard_input, this);
	components = new data::data_vector<game_component*>();
	components->add(map);
	components->add(input);
}

game::game::~game()
{
	running = false;
	components->for_each([](int idx, game_component* component) {
		delete component;
	});
	delete components;

	// those gets deleted along with the components
	map = nullptr;
	input = nullptr;
}

bool game::game::is_running()
{
	return running;
}

void game::game::on_keyboard_input(int keyboard_key)
{
	
}


void game::game::tick()
{
	components->for_each([](int idx, game_component* component) {
		if(component)
			component->tick();
	});
}

void game::game::render()
{
	std::cout << console_code::reset_cursor_position << console_code::hide_cursor;
	components->for_each([](int idx, game_component* component) {
		if(component)
			component->render();
	});
}
