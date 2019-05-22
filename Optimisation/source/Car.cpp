#include "../inc/algocoll.hpp"

Car::Car(double lenght, double hight) : m_lenght(lenght), m_hight(hight)
{}

Car::Car() = default;

Car::~Car()
{
    m_coords.clear();
    m_coords_init.clear();
}
