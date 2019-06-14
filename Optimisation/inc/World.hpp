#ifndef WORLD_HPP
#define WORLD_HPP
#include <iostream>
#include <vector>

enum typeFlags {
    GERBEUR = 1,
    PITS = 2,
};

class Truck
{
public:
	double m_position;
	typeFlags m_type;
};

class Gerbeur : public Truck // 1
{
public:
	int get_max_angle() { return m_max_angle; }
	void set_max_angle(int max) { m_max_angle = max; }
private:
	int m_max_angle;
};

class Pits : public Truck // 2
{
public:
	double get_lenght() { return m_lenght; }
	void set_lenght(double lenght) { m_lenght = lenght; }
	double get_depht() { return m_depth; }
	void set_depht(double depht) { m_depth = depht; }
private:
	double m_lenght;
	double m_depth; // profondeur
};

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
	std::vector<Truck *> m_params;

private :
	bool m_debug_flag;
	bool m_visu_flag;
	double m_limite_camion;
	double m_step;
};

#endif
