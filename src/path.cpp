#include "path.hpp"

path::path(){}

path::~path(){}



int path::get_last_x()
{
    return path_[path_.size() - 1].get_x();
}



int path::get_last_y()
{
    return path_[path_.size() - 1 ].get_y();
}



int path::get_before_last_x()
{
    return path_[path_.size() - 2].get_x();
}



int path::get_before_last_y()
{
    return path_[path_.size() - 2].get_y();
}


int path::get_size()
{
    return path_.size();
}



int path::get_cost()
{
    return total_cost;
}



void path::add(int coor_x, int coor_y)
{
    node aux(coor_x,coor_y);
    path_.push_back(aux);
}


void path::update_cost(float cost)
{
    total_cost = cost;
}



path path::get_path() {
    path aux;

    for (int i = 0; i< path_.size(); i++) {
        aux.add(path_[i].get_x(),path_[i].get_y());
    }
    aux.copy_total_cost(total_cost);

    return aux;
}


void path::copy_total_cost(int cost)
{
    total_cost = cost;
}



node path::operator[](int i)
{
    return path_[i];
}
