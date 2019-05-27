#include "../inc/algocoll.hpp"

bool move_car(World *env, std::vector<Car> *Lot, int cars_placed, std::vector<Car> *map)
{
	int index;
	int checkp_ret = 0;
	int collision_ret = car_collision((*Lot)[cars_placed], (*Lot)[cars_placed].m_coords.size(), map);
	for (auto map_c : (*map))
	{
		while (collision_ret)
		{
			DEBUGP printf("\e[31m\tCan't place Car%d at pos %f\e[39m\n", cars_placed, (*Lot)[cars_placed].m_shift);
			checkp_ret = check_params(env, &(*Lot)[cars_placed]);
			if (!checkp_ret)
			{
				if ((*Lot)[cars_placed].m_shift + collision_ret < env->GetLimiteCamion())
					(*Lot)[cars_placed].m_shift = collision_ret + 50;
				else
					(*Lot)[cars_placed].m_shift += env->GetStep();
				if ((*Lot)[cars_placed].m_lenght + (*Lot)[cars_placed].m_shift >= env->GetLimiteCamion())
				{
					DEBUGP printf("\e[31m\t\tLeave cause of the limite\e[39m\n");
					return false;
				}
				index = 0;
				for (auto tmp : (*Lot)[cars_placed].m_coords)
				{
					(*Lot)[cars_placed].m_coords[index].x = (*Lot)[cars_placed].m_coords_init[index].x + (*Lot)[cars_placed].m_shift;
					(*Lot)[cars_placed].m_coords[index].y = (*Lot)[cars_placed].m_coords_init[index].y;
					index++;
				}
			}
			collision_ret = car_collision((*Lot)[cars_placed], (*Lot)[cars_placed].m_coords.size(), map);
			if (checkp_ret == 2)
			{
				index = 0;
				(*Lot)[cars_placed].m_shift += env->GetStep();
				for (auto tmp : (*Lot)[cars_placed].m_coords)
				{
					(*Lot)[cars_placed].m_coords[index].x = (*Lot)[cars_placed].m_coords_init[index].x + (*Lot)[cars_placed].m_shift;
					(*Lot)[cars_placed].m_coords[index].y = (*Lot)[cars_placed].m_coords_init[index].y;
					index++;
				}
			}
		}
		if ((*Lot)[cars_placed].m_shift + (*Lot)[cars_placed].m_lenght >= env->GetLimiteCamion())
		{
			DEBUGP printf("\e[31m\t\tLeave cause of the limite but wout collision\e[39m\n");
			return false;
		}
	}
	return true;
}

int place_cars(World *env, std::vector<Car>* Lot, int number_cars, std::vector<Car>* map, int index)
{
	static int cars_placed;
	static int number_call;

	while (cars_placed != number_cars)
	{
		// Coder le visu ici
		number_call++;
		DEBUGP printf("Number call = %d\n", number_call);
		DEBUGP std::cout << "\e[34mPlacing = " << cars_placed << "\e[39m" << std::endl;
		if (move_car(env, Lot, cars_placed, map)) // we move following car following the route until it can be placed
		{
			(*map).push_back((*Lot)[cars_placed]);
			DEBUGP printf("\t\t\e[32mCar%d added on the map at %f\e[39m\n", cars_placed, (*Lot)[cars_placed].m_shift);
			cars_placed += 1;
		}
		else
		{
			(*map).pop_back();
			DEBUGP printf("\e[31m\tCar%lu as been deleted from the map\e[39m\n", (*map).size());
			index = 0;
			for (auto tmp : (*Lot)[cars_placed].m_coords)
			{
				(*Lot)[cars_placed].m_coords[index].x = (*Lot)[cars_placed].m_coords_init[index].x;
				index++;
			}
			(*Lot)[cars_placed].m_shift = 0.0f;
			cars_placed -= 1;
			if ((*map).size() <= 0 && (*Lot)[cars_placed].m_lenght + (*Lot)[cars_placed].m_shift >= env->GetLimiteCamion())
				return -1;
			(*Lot)[cars_placed].m_shift += env->GetStep();
			index = 0;
			for (auto tmp : (*Lot)[cars_placed].m_coords)
			{
				(*Lot)[cars_placed].m_coords[index].x  = (*Lot)[cars_placed].m_coords_init[index].x + (*Lot)[cars_placed].m_shift;
				index++;
			}
		}
		VISUP{
				for (auto tmp : (*map))
				{
					std::cout << "------" << std::endl;
					for (auto point : tmp.m_coords)
					{
						std::cout << point.x <<"||"<< point.y << std::endl;
					}
				}
				std::cout << "END MAP" << std::endl;
			}
	}
	return (0);
}
