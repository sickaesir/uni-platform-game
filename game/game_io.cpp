#include "../common.hpp"
#include "game_io.hpp"


game::game_io::game_io(game_component* parent) : game_component(parent, "game_input")
{
	raw();
	initscr();
	nocbreak();
	nodelay(stdscr, true);
	noecho();
	curs_set(0);
}

void game::game_io::init_colors()
{
	start_color();
	auto init_color_pair = [](console::color color, short int color_code) {
		init_pair((short int)color, COLOR_BLACK, color_code);
	};

	init_color_pair(console::color::black, COLOR_BLACK);
	init_color_pair(console::color::blue, COLOR_BLUE);
	init_color_pair(console::color::green, COLOR_GREEN);
	init_color_pair(console::color::cyan, COLOR_CYAN);
	init_color_pair(console::color::red, COLOR_RED);
	init_color_pair(console::color::magenta, COLOR_MAGENTA);
	init_color_pair(console::color::yellow, COLOR_YELLOW);
	init_color_pair(console::color::white, COLOR_WHITE);
	init_color(COLOR_BLUE, 1000, 0, 0);
}

game::game_io::~game_io()
{

}

void game::game_io::tick()
{
	int current_char = getch();
	if(current_char == -1) return;

	log("received keyboard input -> 0x%04x", current_char);
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

void game::game_io::draw(int x, int y, console::color color, bool bright, const char* format, ...)
{
	char buffer[256];
	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	printw("\x1b[38;2;255;100;0m\r", (int)color);
	move(y, x);
	printw(buffer);
//	attroff(COLOR_PAIR((short int)color));
}
