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

int check_params(World *env, Car *car) //prend le env qui contiendra les gerbeurs et les pits
{
    double position = (*car).m_shift;
	double known_position_gerbeur = 9000;
	double known_position_pit = 5000;
	if (position >= known_position_gerbeur - 500 && position <= known_position_gerbeur + 100)
	{
        gerbeur_holder(env, car);
        return 1;
    }
    else if (position >= known_position_pit - 200 && position <= known_position_pit + 600)
    {
        pits_holder(env, car);
        return 2;
    }
    return 0;
}
