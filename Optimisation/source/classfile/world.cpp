#include "../../inc/algocoll.hpp"

World::World(double limite_camion, double step) : m_debug_flag(false),
    m_visu_flag(false), m_limite_camion(limite_camion), m_step(step)
{}

World::~World() {}

bool World::GetDebugFlag() { return m_debug_flag; }

bool World::GetVisuFlag() { return m_visu_flag; }

double World::GetLimiteCamion() { return m_limite_camion; }

double World::GetStep() { return m_step; }

void World::SetDeBugFlag(bool status) { m_debug_flag = status; }

void World::SetVisuFlag(bool status) { m_visu_flag = status; }

void World::SetLimiteCamion(double new_limite) { m_limite_camion = new_limite; }

void World::SetStep(double new_step) { m_step = new_step; }
