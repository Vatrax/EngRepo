#include "robot.hh"

float robot::wez_x()
{
	return x;
}

float robot::wez_y()
{
	return y;
}

void robot::ustal_x(int new_x)
{
	x = new_x;
}

void robot::ustal_y(int new_y)
{
	y = new_y;
}
