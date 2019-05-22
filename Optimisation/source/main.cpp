#include "../inc/algocoll.hpp"

bool debug_flag = false;
bool visu_flag = false;
double limite_camion = 19000.0f;
double step = 100.0f;

void reset_angle(Car *car)
{
	int index = 0;
	for (auto tmp : (*car).m_coords)
	{
		(*car).m_coords[index].x = (*car).m_coords_init[index].x + (*car).m_shift;
		index++;
	}
}

bool check_params(double position)
{
	double known_position = 12000;
	if (position >= known_position - 500 && position <= known_position + 100)
		return true;
	return false;
}

void gerbeur_holder(Car *car)
{
	double gerbeur_x = 12000;
	int max_angle = -35;
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
		(*car).m_shift += step;
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
		//printf("Rotate : x = %f, y = %f at index : %d\n", tmpx, tmpy, index);
	}
	angle -= 3;
}

bool move_car(std::vector<Car> *Lot, int cars_placed, std::vector<Car> *map)
{
	int index;
	int collision_ret = car_collision((*Lot)[cars_placed], (*Lot)[cars_placed].m_coords.size(), map);
	for (auto map_c : (*map))
	{
		while (collision_ret)
		{
			DEBUG printf("\e[31m\tCan't place Car%d at pos %f\e[39m\n", cars_placed, (*Lot)[cars_placed].m_shift);
			//printf("%f\n", (*Lot)[cars_placed].m_shift + (*Lot)[cars_placed].m_lenght);
			if (check_params((*Lot)[cars_placed].m_shift))
				gerbeur_holder((&(*Lot)[cars_placed]));
			else
			{
				if ((*Lot)[cars_placed].m_shift + collision_ret < limite_camion)
					(*Lot)[cars_placed].m_shift = collision_ret + 50;
				else
					(*Lot)[cars_placed].m_shift += step;
				if ((*Lot)[cars_placed].m_lenght + (*Lot)[cars_placed].m_shift >= limite_camion)
				{
					DEBUG printf("\e[31m\t\tLeave cause of the limite\e[39m\n");
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
		}
		if ((*Lot)[cars_placed].m_shift + (*Lot)[cars_placed].m_lenght >= limite_camion)
		{
			DEBUG printf("\e[31m\t\tLeave cause of the limite but wout collision\e[39m\n");
			return false;
		}
	}
	return true;
}

int place_cars(std::vector<Car>* Lot, int number_cars, std::vector<Car>* map, int index)
{
	static int cars_placed;
	static int number_call;

	while (cars_placed != number_cars)
	{
		// Coder le visu ici
		number_call++;
		DEBUG printf("Number call = %d\n", number_call);
		DEBUG std::cout << "\e[34mPlacing = " << cars_placed << "\e[39m" << std::endl;
		if (move_car(Lot, cars_placed, map)) // we move following car following the route until it can be placed
		{
			(*map).push_back((*Lot)[cars_placed]);
			DEBUG printf("\t\t\e[32mCar%d added on the map at %f\e[39m\n", cars_placed, (*Lot)[cars_placed].m_shift);
			cars_placed += 1;
		}
		else
		{
			(*map).pop_back();
			DEBUG printf("\e[31m\tCar%lu as been deleted from the map\e[39m\n", (*map).size());
			index = 0;
			for (auto tmp : (*Lot)[cars_placed].m_coords)
			{
				(*Lot)[cars_placed].m_coords[index].x = (*Lot)[cars_placed].m_coords_init[index].x;
				index++;
			}
			(*Lot)[cars_placed].m_shift = 0.0f;
			cars_placed -= 1;
			if ((*map).size() <= 0 && (*Lot)[cars_placed].m_lenght + (*Lot)[cars_placed].m_shift >= limite_camion)
				return -1;
			(*Lot)[cars_placed].m_shift += step;
			index = 0;
			for (auto tmp : (*Lot)[cars_placed].m_coords)
			{
				(*Lot)[cars_placed].m_coords[index].x  = (*Lot)[cars_placed].m_coords_init[index].x + (*Lot)[cars_placed].m_shift;
				index++;
			}
		}
		VISU{
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

int main(int ac, char **av)
{
	std::vector<Car> Lot;
	std::vector<Car> map;
	Car carA(5271, 1496);
	Car carD(5271, 1496);
	Car carB(4924, 1797);
	Car carC(4924, 1797);
	Point P;
	int index = 0;

	while (++index < ac)
	{
		std::string s(av[index]);
		if (!s.find("-P"))
		{
			step = atof(av[index] + 2);
			if (step <= 0)
				step = 500;
			std::cout << "Soft Precision with step = " << step << std::endl;
		}
		if (!strcmp(av[index], "-D"))
			debug_flag = true;
		if (!strcmp(av[index], "-V"))
			visu_flag = true;
		if (strcmp(av[index], "-D") && strcmp(av[index], "-V") && s.find("-P"))
			std::cout << "Flag \"" << av[index] << "\" does not exist\nPlease Use -D or -V or -P(step)" << std::endl;
		if (visu_flag && debug_flag)
		{
			std::cout << "-V and -D can't be used at the same time\n-D for Debug\n-V for the Visu\n-Opti for optimisation" << std::endl;
			return (0);
		}
	}

	index = 0;

	P.x = 1500;
	P.y = 1500;
	//Points : Mercedes class S Long
	carA.m_coords.push_back(Point(0, 0));
	carA.m_coords.push_back(Point(5271, 0));
	carA.m_coords.push_back(Point(5271, 897.6));
	carA.m_coords.push_back(Point(4054.45, 897.6));
	carA.m_coords.push_back(Point(3109.89, 1496));
	carA.m_coords.push_back(Point(1317.75, 1496));
	carA.m_coords.push_back(Point(527.1, 1047.2));
	carA.m_coords.push_back(Point(0, 1047.2));
	carA.m_coords_init = carA.m_coords;
	carA.ID = 0;
	Lot.push_back(carA);
	//Points : Mercedes CLE SUV
	carB.m_coords.push_back(Point(0, 0));
	carB.m_coords.push_back(Point(4924, 0));
	carB.m_coords.push_back(Point(4924, 1168.05));
	carB.m_coords.push_back(Point(3787.54, 1347.75));
	carB.m_coords.push_back(Point(3030.23, 1797));
	carB.m_coords.push_back(Point(757.31, 1797));
	carB.m_coords.push_back(Point(0, 1347.75));
	carB.m_coords_init = carB.m_coords;
	carB.ID = 1;
	Lot.push_back(carB);
	carC.m_coords.push_back(Point(0, 0));
	carC.m_coords.push_back(Point(4924, 0));
	carC.m_coords.push_back(Point(4924, 1168.05));
	carC.m_coords.push_back(Point(3787.54, 1347.75));
	carC.m_coords.push_back(Point(3030.23, 1797));
	carC.m_coords.push_back(Point(757.31, 1797));
	carC.m_coords.push_back(Point(0, 1347.75));
	carC.m_coords_init = carB.m_coords;
	carC.ID = 1;
	Lot.push_back(carC);
	carD.m_coords.push_back(Point(0, 0));
	carD.m_coords.push_back(Point(5271, 0));
	carD.m_coords.push_back(Point(5271, 897.6));
	carD.m_coords.push_back(Point(4054.45, 897.6));
	carD.m_coords.push_back(Point(3109.89, 1496));
	carD.m_coords.push_back(Point(1317.75, 1496));
	carD.m_coords.push_back(Point(527.1, 1047.2));
	carD.m_coords.push_back(Point(0, 1047.2));
	carD.m_coords_init = carA.m_coords;
	carD.ID = 1;
	Lot.push_back(carD);

	if (place_cars(&Lot, Lot.size(), &map, index) == -1)
	{
		VISU std::cout << "END VISU" << std::endl;
		printf("Impossible de placer le Lot\n");
	}
	else
	{
		VISU std::cout << "END VISU" << std::endl;
		for (auto tmp : Lot)
		{
			std::cout << "We placed a car at " << tmp.m_shift << "mm" <<  std::endl;
			DEBUG std::cout << "His lenght was " << tmp.m_lenght << "mm" <<  std::endl;
		}
	}
	carA.m_coords.clear();
	carB.m_coords.clear();
	carD.m_coords.clear();
	return (0);
}
