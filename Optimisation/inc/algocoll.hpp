#ifndef ALGOCOLL_H
#define ALGOCOLL_H

#include <iostream>
#include <vector>
#include <math.h>
#include "Car.hpp"
#include "Point.hpp"
#include "Vecteur.hpp"
#include "World.hpp"

# define DEBUG	if (env.GetDebugFlag())
# define VISU	if (env.GetVisuFlag())
# define DEBUGP	if (env->GetDebugFlag())
# define VISUP	if (env->GetVisuFlag())

int intersectsegment(Point A,Point B,Point I,Point P);

bool Collision(Car tab, int nbp, Point P);

int car_collision(Car car2, size_t nbp_car2, std::vector<Car> *map);

void reset_angle(Car *car);

bool check_params(World *env, double position);

void gerbeur_holder(World *env, Car *car);

bool move_car(World *env, std::vector<Car> *Lot, int cars_placed, std::vector<Car> *map);

int place_cars(World *env, std::vector<Car>* Lot, int number_cars, std::vector<Car>* map, int index);

#endif
