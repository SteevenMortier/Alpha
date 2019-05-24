#include "../inc/algocoll.hpp"

double calc_angle(Car *car, double pit_high)
{
    if (pit_high < 0)
        pit_high *= -1;
    return (atan(pit_high / (*car).m_lenght));
}

void pits_holder(World *env, Car *car)
{
    double pit_position = 5000;
    double pit_high = -500;
    double pit_lenght = 500;
    double angle = calc_angle(car, pit_high);
    int index = 0;

    for (auto coord : (*car).m_coords)
	{
		double tmpx;
		double tmpy;
		coord.x = (coord.x - pit_position);
		coord.y = coord.y - 0;
		tmpx = pit_position + coord.x * cos(angle * (M_PI / 180)) - coord.y * sin(angle * (M_PI / 180));
		tmpy = 0 + coord.x * sin(angle * (M_PI / 180)) + coord.y * cos(angle * (M_PI / 180));
		(*car).m_coords[index].x = tmpx;
		(*car).m_coords[index].y = tmpy;
		index++;
		//printf("Rotate : x = %f, y = %f at index : %d\n", tmpx, tmpy, index);
	}
}
