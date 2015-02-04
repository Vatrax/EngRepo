#ifndef _ROBOT_HH
#define _ROBOT_HH

class robot
{
	public:
	robot(){x=y=0;};
	float wez_x();
	float wez_y();
	void ustal_x(float x);
	void ustal_y(float y);
	private:
	int x,y;
};

#endif
