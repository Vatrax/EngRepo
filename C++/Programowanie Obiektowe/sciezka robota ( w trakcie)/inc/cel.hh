#ifndef _CEL_
#define _CEL_
#include <math.h>


class cel
{
	public:
	cel(){x=y=ladunek=0; wzmocnienie = 3;}
	float wez_x();
	float wez_y();
	void ustal_x(float x);
	void ustal_y(float y);
	int wez_ladunek();
	void ustal_ladunek(int ladunek);
	float wylicz_potencjal(float x, float y);
	private:
	int ladunek,rozmiar, wzmocnienie;
	float x,y;
};

#endif
