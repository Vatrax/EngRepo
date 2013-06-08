#include "cel.hh"

float cel::wez_x()
{
	return x;
}

float cel::wez_y()
{
	return y;
}

void cel::ustal_x(float new_x)
{
	x = new_x;
}

void cel::ustal_y(float new_y)
{
	y = new_y;
}

int cel::wez_ladunek()
{
	return ladunek;
}

void cel::ustal_ladunek(int new_ladunek)
{
	ladunek = new_ladunek;
}

float cel::wylicz_potencjal(float x_sceny, float y_sceny)
{
	float potencjal = 0;
	
	potencjal = - (wzmocnienie / sqrt(  (x - x_sceny) * (x - x_sceny) + (y - y_sceny) * (y - y_sceny) + 1 )); 
	return potencjal;	
}
