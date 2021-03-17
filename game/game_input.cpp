#include "../common.hpp"
#include "game_input.hpp"
#include <ncurses.h>

template<class elem_t>
game::game_input<elem_t>::game_input() :
	input_callback(nullptr),
	callback_instance(nullptr)
{

}

template<class elem_t>
game::game_input<elem_t>::~game_input()
{

}

template<class elem_t>
void game::game_input<elem_t>::set_input_callback(void(elem_t::*callback)(int), elem_t* instance)
{
	input_callback = callback;
	callback_instance = instance;
}

template<class elem_t>
void game::game_input<elem_t>::tick()
{
	int current_char = getch();
	if(current_char && input_callback)
		(callback_instance->*input_callback)(current_char);
}

template<class elem_t>
void game::game_input<elem_t>::render()
{

}

template<class elem_t>
bool game::game_input<elem_t>::on_keyboard(int character)
{
	return false;
}
