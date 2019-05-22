#ifndef ALGOCOLL_H
#define ALGOCOLL_H

#include <iostream>
#include <vector>
#include <math.h>
#include "Car.hpp"
#include "Point.hpp"
#include "Vecteur.hpp"
#include "World.hpp"

# define DEBUG	if (debug_flag)
# define VISU	if (visu_flag)

int intersectsegment(Point A,Point B,Point I,Point P);

bool Collision(Car tab, int nbp, Point P);

int car_collision(Car car2, size_t nbp_car2, std::vector<Car> *map);

#endif
