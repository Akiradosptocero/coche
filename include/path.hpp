#pragma once
#include "node.hpp"
#include <vector>

class path
{
private:
    std::vector<node> path_;
    int total_cost;

public:

    path();
    ~path();


    path get_path();
    int get_last_x();
    int get_last_y();
    int get_before_last_x();
    int get_before_last_y();

    int get_x(int i);
    int get_y(int j);

    int get_size();

    int get_cost();

    void add(int x, int y);
    void update_cost(float cost);

    void copy_total_cost(int cost);

    node operator[](int x);
};
