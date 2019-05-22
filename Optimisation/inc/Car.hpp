#ifndef CAR_HPP
#define CAR_HPP
#include <iostream>
#include <vector>
#include "Point.hpp"

class Car
{
public:
	Car(double lenght, double hight);
	Car();
	~Car();
	std::vector<Point> m_coords;
	std::vector<Point> m_coords_init;
	double m_lenght;
	int ID;
	double m_hight;
	double m_shift;
};

#endif
