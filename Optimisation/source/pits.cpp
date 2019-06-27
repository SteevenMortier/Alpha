#include "../inc/algocoll.hpp"

double calc_angle(Car *car, double pit_high)
{
    if (pit_high < 0)
        pit_high *= -1;
    //printf("On a atan(%f / %f) = %f\n", pit_high, (*car).m_lenght, (180 * atan(pit_high / (*car).m_lenght)) / M_PI);
    return ((180 * atan(pit_high / (*car).m_lenght)) / M_PI);
}

void put_angle(Car *car, double angle, double pit_position, double pit_high)
{
    int index = 0;

    reset_angle(car);
    for (auto coord : (*car).m_coords)
    {
        double tmpx;
        double tmpy;
        coord.x = coord.x - pit_position;
        coord.y = coord.y;
        tmpx = pit_position + coord.x * cos(angle * (M_PI / 180)) - coord.y * sin(angle * (M_PI / 180));
        tmpy = 0 + coord.x * sin(angle * (M_PI / 180)) + coord.y * cos(angle * (M_PI / 180)); // 0 because the gerbeur is at 0 on y, if it change juste change by the y of the gerbeur
        tmpy = tmpy + pit_high; // inversed
        (*car).m_coords[index].x = tmpx;
        (*car).m_coords[index].y = tmpy;
        index++;
        //printf("Rotate : x = %f, y = %f at index : %d\n", tmpx, tmpy, index);
    }
}

void pits_holder(World *env, Car *car)
{
    double pit_position = static_cast<Pits *>((*env).m_params[(*env).GetIndex()])->m_position;
    double car_end_position = (*car).m_shift + (*car).m_lenght;
    double pit_high = static_cast<Pits *>((*env).m_params[(*env).GetIndex()])->get_depht();
    double pit_lenght = static_cast<Pits *>((*env).m_params[(*env).GetIndex()])->get_lenght();
    double angle = calc_angle(car, pit_high);

    if (in_range((*car).m_shift, pit_position - pit_lenght, pit_position + pit_lenght)) // negative angle
        put_angle(car, angle, pit_position, pit_high);
    else if (in_range(car_end_position, pit_position - pit_lenght, pit_position + pit_lenght)) //positive angle
        put_angle(car, angle * -1, pit_position, pit_high);
}
