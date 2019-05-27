#include "../inc/algocoll.hpp"

double calc_angle(Car *car, double pit_high)
{
    if (pit_high < 0)
        pit_high *= -1;
    //printf("On a atan(%f / %f) = %f\n", pit_high, (*car).m_lenght, (180 * atan(pit_high / (*car).m_lenght)) / M_PI);
    return ((180 * atan(pit_high / (*car).m_lenght)) / M_PI);
}

void pits_holder(World *env, Car *car)
{
    double pit_position = 5000;
    double pit_high = -500;
    double pit_lenght = 500;
    double angle = 40;//calc_angle(car, pit_high);
    int index = 0;

    reset_angle(car);
    //printf("Pits angle : %f\n", angle);
    for (auto coord : (*car).m_coords)
	{
		double tmpx;
		double tmpy;
		coord.x = coord.x - pit_position;
		coord.y = coord.y;
		tmpx = pit_position + coord.x * cos(angle * (M_PI / 180)) - coord.y * sin(angle * (M_PI / 180));
		tmpy = 0 + coord.x * sin(angle * (M_PI / 180)) + coord.y * cos(angle * (M_PI / 180));
		(*car).m_coords[index].x = tmpx;
		(*car).m_coords[index].y = tmpy;
		index++;
		//printf("Rotate : x = %f, y = %f at index : %d\n", tmpx, tmpy, index);
	}
    //(*car).m_shift += env->GetStep();
}
