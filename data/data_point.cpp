#include "data_point.hpp"

data::data_point::data_point() :
	x_pos(0),
	y_pos(0)
{
}

data::data_point::data_point(int _x, int _y) :
	x_pos(_x),
	y_pos(_y)
{
}

data::data_point::~data_point()
{
}

int data::data_point::x()
{
	return x_pos;
}

int data::data_point::y()
{
	return y_pos;
}

void data::data_point::y(int _y)
{
	y_pos = _y;
}

void data::data_point::x(int _x)
{
	x_pos = _x;
}
