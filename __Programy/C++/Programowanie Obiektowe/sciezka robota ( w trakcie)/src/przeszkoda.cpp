#include "przeszkoda.hh"

float przeszkoda::wez_x()
{
	return x;
}

float przeszkoda::wez_y()
{
	return y;
}

void przeszkoda::ustaw_x(float new_x)
{
	x = new_x;
}

void przeszkoda::ustaw_y(float new_y)
{
	y = new_y;
}

int przeszkoda::wez_rozmiar()
{
	return rozmiar;
}

void przeszkoda::ustaw_rozmiar(int new_rozmiar)
{
	rozmiar = new_rozmiar;
}

float przeszkoda::wylicz_potencjal(float x_sceny, float y_sceny)
{
	float potencjal = 0;
	potencjal = 1 / (  ( (x_sceny - x ) * (x_sceny - x ) ) + ( (y_sceny - y ) * (y_sceny - y ) ) - rozmiar * rozmiar + abs( ( (x_sceny - x ) * (x_sceny - x ) ) + ( (y_sceny - y ) * (y_sceny - y ) ) - rozmiar * rozmiar ) + 1 );
	return potencjal;
}
