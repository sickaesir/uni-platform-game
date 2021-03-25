#pragma once
namespace data
{
	class data_point {
	public:
		data_point();
		data_point(int _x, int _y);
		~data_point();

	public:
		int x();
		int y();
		void x(int _x);
		void y(int _y);

	private:
		int x_pos;
		int y_pos;
	};
}
