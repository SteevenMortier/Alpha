#include "../inc/algocoll.hpp"

/*bool in_range(double nbr, double min, double max)
{
	if (nbr >= min && nbr <= max)
		return true;
	return false;
}*/

int main(int ac, char **av)
{
	World env(19000, 100);
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
			env.SetStep(atof(av[index] + 2));
			if (env.GetStep() <= 0)
				env.SetStep(500);
			std::cout << "Soft Precision with step = " << env.GetStep() << std::endl;
		}
		if (!strcmp(av[index], "-D"))
			env.SetDeBugFlag(true);
		if (!strcmp(av[index], "-V"))
			env.SetVisuFlag(true);
		if (strcmp(av[index], "-D") && strcmp(av[index], "-V") && s.find("-P"))
			std::cout << "Flag \"" << av[index] << "\" does not exist\nPlease Use -D or -V or -P(step)" << std::endl;
		if (env.GetVisuFlag() && env.GetDebugFlag())
		{
			std::cout << "-V and -D can't be used at the same time\n-D for Debug\n-V for the Visu\n-Opti for optimisation" << std::endl;
			return (0);
		}
	}

	index = 0;

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
	carA.m_ID = 0;
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
	carB.m_ID = 1;
	Lot.push_back(carB);
	carC.m_coords.push_back(Point(0, 0));
	carC.m_coords.push_back(Point(4924, 0));
	carC.m_coords.push_back(Point(4924, 1168.05));
	carC.m_coords.push_back(Point(3787.54, 1347.75));
	carC.m_coords.push_back(Point(3030.23, 1797));
	carC.m_coords.push_back(Point(757.31, 1797));
	carC.m_coords.push_back(Point(0, 1347.75));
	carC.m_coords_init = carC.m_coords;
	carC.m_ID = 2;
	Lot.push_back(carC);
	carD.m_coords.push_back(Point(0, 0));
	carD.m_coords.push_back(Point(5271, 0));
	carD.m_coords.push_back(Point(5271, 897.6));
	carD.m_coords.push_back(Point(4054.45, 897.6));
	carD.m_coords.push_back(Point(3109.89, 1496));
	carD.m_coords.push_back(Point(1317.75, 1496));
	carD.m_coords.push_back(Point(527.1, 1047.2));
	carD.m_coords.push_back(Point(0, 1047.2));
	carD.m_coords_init = carD.m_coords;
	carD.m_ID = 3;
	Lot.push_back(carD);

	/// Mini algo to reverse all cars in Lot
	int index2;
	index = 0;
	for (auto tmp : Lot)
	{
		index2 = 0;
		for (auto point : tmp.m_coords)
		{
			(Lot)[index].m_coords[index2].x *= -1;
			(Lot)[index].m_coords[index2].x += tmp.m_lenght;
			index2++;
		}
		Lot[index].m_coords_init = (Lot)[index].m_coords;
		index++;
	}
	/// end mini algo

	/// START test of inherance
	Gerbeur *tmpg;
	tmpg = new Gerbeur();
	tmpg->m_position = 7000;
	tmpg->m_type = GERBEUR;
	tmpg->set_max_angle(35);
	env.m_params.push_back(tmpg);

	if (env.m_params[0]->m_type == GERBEUR)
	{
        std::cout << static_cast<Gerbeur *>(env.m_params[0])->get_max_angle() << std::endl;
    }
	///

	if (place_cars(&env, &Lot, Lot.size(), &map, index) == -1)
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
