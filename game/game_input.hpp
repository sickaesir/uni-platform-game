#pragma once
#include "game_component.hpp"
namespace game
{
	template<class elem_t>
	class game_input : public game_component
	{
	public:
		game_input();
		~game_input();

	public:
		void set_input_callback(void(elem_t::*callback)(int), elem_t* instance);
		virtual void render() override;
		virtual void tick() override;
		virtual bool on_keyboard(int character) override;

	private:
		void (elem_t::*input_callback)(int);
		elem_t* callback_instance;
	};
}
