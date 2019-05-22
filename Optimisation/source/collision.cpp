#include "../inc/algocoll.hpp"

int intersectsegment(Point A,Point B,Point I,Point P)
{
	Vecteur D,E;
	double u, t;
 	D.x = B.x - A.x;
	D.y = B.y - A.y;
	E.x = P.x - I.x;
	E.y = P.y - I.y;
	double denom = D.x * E.y - D.y * E.x;
 	if (denom == 0)
		return -1;
	t = - (A.x * E.y - I.x * E.y - E.x * A.y + E.x * I.y) / denom;
	if (t < 0 || t >= 1)
		return 0;
	u = - (-D.x *A.y + D.x * I.y + D.y * A.x - D.y * I.x) / denom;
	if (u < 0 || u >= 1)
 		return 0;
	return 1;
}

bool Collision(Car tab, int nbp, Point P)
{
	int		i;
	Point	I;
    int nbintersections = 0;

	I.x = 1000000 + rand() % 100;
	I.y = 1000000 + rand() % 100;
	for(i = 0; i < nbp; i++)
	{
		Point A = tab.m_coords[i];
		Point B;
		if (i == nbp - 1)
			B = tab.m_coords[0];
		else
         	B = tab.m_coords[i + 1];
     	int iseg = intersectsegment(A, B, I, P);
     	if (iseg == -1)
			return false;
     	nbintersections += iseg;
  	}
  	if (nbintersections % 2 == 1)
     		return true;
  	else
     		return false;
}

int car_collision(Car car2, size_t nbp_car2, std::vector<Car> *map)
{
	for (auto map_c : (*map))
	{
		for (auto car : car2.m_coords)
		{
			if (Collision(map_c, map_c.m_coords.size(), car))
				return (map_c.m_lenght + map_c.m_shift);
		}
		for (auto car : map_c.m_coords)
		{
			if (Collision(car2, nbp_car2, car))
				return (map_c.m_lenght + map_c.m_shift);
		}
	}
	return 0;
}
