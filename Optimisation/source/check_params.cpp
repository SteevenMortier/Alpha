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

// Le probleme viens du fait que si il n'y a pas de collision en premier lieu, le gerbeur est lancé une seule fois

int check_params(World *env, Car *car, std::vector<Car> *map) //prend le env qui contiendra les gerbeurs et les pits
{
    double position = (*car).m_shift;
	double car_end_position = (*car).m_shift + (*car).m_lenght;
	double known_position_gerbeur = 7500;
	double known_position_pit = 5000;
	double pit_lenght = 1000;

	reset_angle(car);
	if (in_range<double>(car_end_position, known_position_gerbeur - 300, known_position_gerbeur + 300))
	{
		gerbeur_holder(env, car);
		return 1;
	}
	else if (in_range<double>(position, known_position_pit - pit_lenght, known_position_pit + pit_lenght)
		|| in_range<double>(car_end_position, known_position_pit - pit_lenght, known_position_pit + pit_lenght))
    {
        pits_holder(env, car);
		(*car).m_shift += (*env).GetStep();
        return 2;
	}
    return 0;
}
