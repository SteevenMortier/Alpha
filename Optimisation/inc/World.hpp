#ifndef WORLD_HPP
#define WORLD_HPP
#include <iostream>
#include <vector>

class World
{
public:
	World(double limite_camion, double step);
	~World();
	bool GetDebugFlag();
	void SetDeBugFlag(bool status);
	bool GetVisuFlag();
	void SetVisuFlag(bool status);
	double GetLimiteCamion();
	void SetLimiteCamion(double new_limite);
	double GetStep();
	void SetStep(double new_step);

private :
	bool m_debug_flag;
	bool m_visu_flag;
	double m_limite_camion;
	double m_step;
};

#endif
