#pragma once
#include <vector>
#include <cmath>
#include <list>
#include <curses.h>
#include <cstdlib> 
#include "terrain.hpp"
#include "node.hpp"
#include "path.hpp"
#include "menu.hpp"

class Iatester {

  private:
    terrain T;
    int counter;
    int counter_p;

  public:
    Iatester(std::vector<int> values, bool fromfile);
    ~Iatester(){}

    float heuristic(int start_x, int start_y, int end_x, int end_y, int opt);
    float heuristic_1(int start_x, int start_y, int end_x, int end_y);
    float heuristic_2(int start_x, int start_y, int end_x, int end_y);


    std::list<path> find_new_paths(std::list<path>& new_path_list, path& actual_path, int opt);
    void astar(node start, node end, int opt);
    void astar_grafico(node start, node goal, int opt);
    bool insert_path_close_list(std::list<path>& closed_list, path& path);
    void insert_path_open_list(std::list<path>& open_list, std::list<path>& close_list, path path);
    void sort_list(std::list<path>& source_list);
};
