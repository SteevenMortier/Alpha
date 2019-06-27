#include "../inc/algocoll.hpp"

void gerbeur_holder(World *env, Car *car)
{
	double gerbeur_x = static_cast<Gerbeur *>((*env).m_params[(*env).GetIndex()])->m_position;
	int max_angle = static_cast<Gerbeur *>((*env).m_params[(*env).GetIndex()])->get_max_angle();
	static int angle = 0;
	int index = 0;
	reset_angle(car);
	for (auto tmp : (*car).m_coords)
	{
		(*car).m_coords[index].x = (*car).m_coords_init[index].x + gerbeur_x - (*car).m_lenght - 200;
		(*car).m_coords[index].y = (*car).m_coords_init[index].y;
		index++;
	}
	//std::cout << "angle = " << angle << std::endl;
	if (angle <= max_angle)
	{
		angle = 0;
		(*car).m_shift += (*env).GetStep();
		reset_angle(car);
	}
	index = 0;
	for (auto coord : (*car).m_coords)
	{
		double tmpx;
		double tmpy;
		coord.x = (coord.x - gerbeur_x);
		coord.y = coord.y - 0;
		tmpx = gerbeur_x + coord.x * cos(angle * (M_PI / 180)) - coord.y * sin(angle * (M_PI / 180));
		tmpy = 0 + coord.x * sin(angle * (M_PI / 180)) + coord.y * cos(angle * (M_PI / 180));
		(*car).m_coords[index].x = tmpx;
		(*car).m_coords[index].y = tmpy;
		index++;
	}
	angle -= 3;
}
