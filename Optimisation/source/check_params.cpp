#include "../inc/algocoll.hpp"

void reset_angle(Car *car)
{
	int index = 0;
	for (auto tmp : (*car).m_coords)
	{
		(*car).m_coords[index].x = (*car).m_coords_init[index].x + (*car).m_shift;
		(*car).m_coords[index].y = (*car).m_coords_init[index].y;
		index++;
	}
}

int check_params(World *env, Car *car, std::vector<Car> *map) //prend le env qui contiendra les gerbeurs et les pits
{
    double position = (*car).m_shift;
	double car_end_position = (*car).m_shift + (*car).m_lenght;
	//printf("Car lenght : %f\n", car_end_position);
	double known_position_gerbeur = 7500;
	double known_position_pit = 5000;
	double pit_lenght = 1000;
	if (in_range<double>(position, known_position_pit - pit_lenght, known_position_pit + pit_lenght)
		|| in_range<double>(car_end_position, known_position_pit - pit_lenght, known_position_pit + pit_lenght))
    {
		//printf("Pit spotted\n");
        pits_holder(env, car);
        return 2;
    }
	if (in_range<double>(car_end_position, known_position_gerbeur - 300, known_position_gerbeur + 300))
	{
		while(car_collision((*car), (*car).m_coords.size(), map))
        	gerbeur_holder(env, car);
        return 1;
    }
    return 0;
}
