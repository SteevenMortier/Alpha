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
	double car_end_position = (*car).m_shift + (*car).m_lenght;
	double known_position_gerbeur = 0;
	double known_position_pit = 0;
	double pit_lenght = 0;
	int index = 0;

	reset_angle(car);
	while (static_cast<size_t>(index) < (*env).m_params.size())
    {
        if ((*env).m_params[index]->m_type == GERBEUR)
        {
			known_position_gerbeur = static_cast<Gerbeur *>((*env).m_params[index])->m_position;
			if (in_range<double>(car_end_position, known_position_gerbeur - 300, known_position_gerbeur + 300))
			{
				(*env).SetIndex(index);
				gerbeur_holder(env, car);
				return 1;
			}
            //std::cout << "We got a Gerbeur of size : ";
            //std::cout << static_cast<Gerbeur *>((*env).m_params[index])->get_max_angle() << std::endl;
        }
        else if ((*env).m_params[index]->m_type == PITS)
        {
			known_position_pit = static_cast<Pits *>((*env).m_params[index])->m_position;
			pit_lenght = static_cast<Pits *>((*env).m_params[index])->get_lenght();
			if (in_range<double>(position, known_position_pit - pit_lenght, known_position_pit + pit_lenght)
				|| in_range<double>(car_end_position, known_position_pit - pit_lenght, known_position_pit + pit_lenght))
		    {
				(*env).SetIndex(index);
		        pits_holder(env, car);
				(*car).m_shift += 100;//(*env).GetStep(); //Dans le pit on avance lentement
		        return 2;
			}
            //std::cout << "We got a Pit of lenght : ";
            //std::cout << static_cast<Pits *>((*env).m_params[index])->get_lenght() << std::endl;
        }
        index++;
    }
    return 0;
}
