#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <ncurses.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>


#include "../include/termcolor.hpp"

using namespace termcolor;

class terrain
{
private:

    // Ancho, alto, matriz con el terreno generado
    int m_;
    int n_;
    std::pair<int,int> final_;
    std::pair<int,int> car_;
    std::vector<std::vector<char>> M_;

public:

    terrain(){}
    terrain(int m, int n, int p, bool fromfile);
    ~terrain();

    //Random Generation or Custom Generation from file
    void random_generation(int p);
    void custom_generation(void);

    char get_pos(int i, int j);
    void set_pos(int i, int j, char a);
    void write_map(void);
    void write_map_grafico(void);

    std::pair<int,int> get_end(void);
    std::pair<int, int> get_car(void);

    bool is_free(int x, int y);
    bool has_end(void);

    int get_m(void);
    int get_n(void);

    void fill(void);

};
