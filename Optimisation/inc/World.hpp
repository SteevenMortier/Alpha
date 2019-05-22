#ifndef WORLD_HPP
#define WORLD_HPP
#include <iostream>
#include <vector>
#include "World.hpp"

class World
{
public:
	World();
	~World();
	bool debug_flag = false;
	bool visu_flag = false;
	double limite_camion = 19000.0f;
	double step = 100.0f;
};

#endif
