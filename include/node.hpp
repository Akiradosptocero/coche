#pragma once
#include <iostream>


class node
{
private:
    int x_;
    int y_;

public:


    node();
    node(int x, int y);

    int get_x(){    return x_;  }
    int get_y(){    return y_;  }

    void set_node(int x, int y);


};
