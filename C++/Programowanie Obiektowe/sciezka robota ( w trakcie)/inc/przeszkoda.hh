#ifndef _PRZESZKODA_HH
#define _PRZESZKODA_HH
#include <stdio.h>
#include <stdlib.h>

class przeszkoda
{
	public:
	przeszkoda(){x=y=rozmiar=0;};
	float wez_x();
	float wez_y();
	void ustaw_x(float x);
	void ustaw_y(float y);
	int wez_rozmiar();
	void ustaw_rozmiar(int x);
	float wylicz_potencjal(float x, float y);
	private:
	float x,y;
	int rozmiar;
};

#endif
