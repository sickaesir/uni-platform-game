#include "../common.hpp"
#include "game_io.hpp"
#include "game_settings.hpp"

game::game_io::game_io(game_component* parent) : game_component(parent, "game_input"),
	inactive_ticks_counter(0)
{
	raw();
	initscr();
	nocbreak();
	nodelay(stdscr, true);
	noecho();
	curs_set(0);
	init_colors();
}

void game::game_io::init_colors()
{
	start_color();
	auto init_color_pair = [](console::color color, short int color_code) {
		init_pair((short int)color, color_code, COLOR_BLACK);
	};

	init_color_pair(console::color::black, COLOR_BLACK);
	init_color_pair(console::color::blue, COLOR_BLUE);
	init_color_pair(console::color::green, COLOR_GREEN);
	init_color_pair(console::color::cyan, COLOR_CYAN);
	init_color_pair(console::color::red, COLOR_RED);
	init_color_pair(console::color::magenta, COLOR_MAGENTA);
	init_color_pair(console::color::yellow, COLOR_YELLOW);
	init_color_pair(console::color::white, COLOR_WHITE);
}

game::game_io::~game_io()
{

}

void game::game_io::tick()
{
	int current_char = getch();

	if(current_char == -1)
	{
		if(inactive_ticks_counter == 0)
		{
			log("no inactive ticks remaining, signaling inactiveness");
			inactive_ticks_counter = -1;
		}
		else if(inactive_ticks_counter == -1)
		{
			return;
		}
		else
		{
			inactive_ticks_counter--;
			return;
		}
	}
	else
		inactive_ticks_counter = get_game_settings()->get_io_inactive_ticks();

	//log("received keyboard input -> 0x%04x", current_char);
	game_component* parent = get_parent();
	if(current_char && parent)
		parent->on_keyboard(current_char);
}

void game::game_io::render()
{

}


bool game::game_io::on_keyboard(int character)
{
	return false;
}

void game::game_io::clear_screen()
{
	erase();
}

void game::game_io::draw(int x, int y, console::color color, bool bright, char character)
{
	const char buffer[2] = { character, 0x00 };
	draw(x, y, color, bright, buffer);
}

void game::game_io::draw(int x, int y, console::color color, bool bright, const char* format, ...)
{
	char buffer[2048];
	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	move(y, x);
	attron(COLOR_PAIR(color));
	if(bright)
		attron(A_BOLD);
	else
		attroff(A_BOLD);
	printw(buffer);
}
