#include "../inc/algocoll.hpp"

void create_gerbeur(World *env, double position, double max_angle)
{
    Gerbeur *tmpg;
    tmpg = new Gerbeur();
    tmpg->m_position = position;
    tmpg->m_type = GERBEUR;
    tmpg->set_max_angle(max_angle);
    (*env).m_params.push_back(tmpg);
}

void create_pit(World *env, double position, double lenght, double depht)
{
    Pits *tmp;
    tmp = new Pits();
    tmp->m_position = position;
    tmp->m_type = PITS;
    tmp->set_lenght(lenght);
    tmp->set_depht(depht);
    (*env).m_params.push_back(tmp);
}

void create_params(World *env)
{
    //int index = 0;
    create_gerbeur(env, 7000, -10);
    create_pit(env, 5000, 1000, -500);
    //create_gerbeur(env, 14000, -35);
    /*while (static_cast<size_t>(index) < (*env).m_params.size())
    {
        if ((*env).m_params[index]->m_type == GERBEUR)
        {
            std::cout << "We got a Gerbeur of size : ";
            std::cout << static_cast<Gerbeur *>((*env).m_params[index])->get_max_angle() << std::endl;
        }
        else if ((*env).m_params[index]->m_type == PITS)
        {
            std::cout << "We got a Pit of lenght : ";
            std::cout << static_cast<Pits *>((*env).m_params[index])->get_lenght() << std::endl;
        }
        index++;
    }*/
}
