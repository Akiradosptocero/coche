#include "../include/iatester.hpp"

Iatester::Iatester(std::vector<int> values, bool fromfile){

    system("clear");
    counter=0;
    counter_p=0;
    T = terrain(values[1], values[2], values[0], fromfile);

    std::pair<int,int> auxstart = T.get_car();
    std::pair<int,int> auxend = T.get_end();

    node start(auxstart.first, auxstart.second);
    node end(auxend.first, auxend.second);

    if(values[3]==1){
      noecho();
      cbreak();
      keypad(stdscr, TRUE);

      while(getch()!=KEY_F(1)){
        erase();
        T.write_map_grafico();
      }
      astar_grafico(start, end, values[4]);
      endwin();
    }
    else
      astar(start, end, values[4]);
}


float Iatester::heuristic(int start_x, int start_y, int end_x, int end_y, int opt)
{
    if(opt == 1){
        float r = sqrt(pow((end_x - (start_x - 1)), 2.0) + pow((end_y - start_y), 2.0));
        return r;
    }

    else if(opt == 2){
        float dif_x = abs(start_x - end_x);
        float dif_y = abs(start_y - end_y);

        float r = dif_x + dif_y;
        return r;
    }

    else
    {
    float r1 = heuristic_1(start_x, start_y, end_x, end_y);
    float r2 = heuristic_2(start_x, start_y, end_x, end_y);

    if(r1 < r2)
        return r1;
    else
        return r2;
    }
}



float Iatester::heuristic_1(int start_x, int start_y, int end_x, int end_y)
{
        float r = sqrt(pow((end_x - (start_x - 1)), 2.0) + pow((end_y - start_y), 2.0));
        return r;
}



float Iatester::heuristic_2(int start_x, int start_y, int end_x, int end_y)
{
    float dif_x = abs(start_x - end_x);
    float dif_y = abs(start_y - end_y);

    float r = dif_x + dif_y;
    return r;

}





        //Encuentra nuevos caminos, y los añade a la lista
std::list<path> Iatester::find_new_paths(std::list<path>& new_path_list,  path& actual_path, int opt)
{
    std::pair<int, int> aux2 = T.get_end();
    int end_x = aux2.first;
    int end_y = aux2.second;

    path aux = actual_path;

    int start_x = actual_path.get_last_x();
    int start_y = actual_path.get_last_y();

    int before_x = actual_path.get_before_last_x();
    int before_y = actual_path.get_before_last_y();

    node nw(start_x -1, start_y);
    node na(start_x, start_y - 1);
    node ns(start_x + 1, start_y);
    node nd(start_x, start_y + 1);

    float cost;

    char w = T.get_pos(start_x -1, start_y);
    char a = T.get_pos(start_x, start_y - 1);
    char s = T.get_pos(start_x + 1, start_y);
    char d = T.get_pos(start_x, start_y + 1);


    if((w != '0') && (start_x > 0)){

        aux.add(nw.get_x(), nw.get_y());

        cost = heuristic(start_x - 1, start_y, end_x, end_y, opt);
        aux.update_cost(cost);

        new_path_list.push_front(aux);

        counter++;
    }

    if((a != '0') && (start_y > 0)){

        aux = actual_path;


        aux.add(na.get_x(), na.get_y());

        cost = heuristic(start_x, start_y - 1, end_x, end_y, opt);
        aux.update_cost(cost);

        new_path_list.push_front(aux);

        counter++;

    }

    if((s != '0') && (start_x < T.get_m())){

        aux = actual_path;

        aux.add(ns.get_x(), ns.get_y());

        cost = heuristic(start_x + 1, start_y, end_x, end_y, opt);
        aux.update_cost(cost);

        new_path_list.push_front(aux);

        counter++;
    }

    if((d != '0') && (start_y < T.get_n())){

        aux = actual_path;


        aux.add(nd.get_x(), nd.get_y());

        cost = heuristic(start_x, start_y + 1, end_x, end_y, opt);
        aux.update_cost(cost);

        new_path_list.push_front(aux);

        counter++;
    }


    return new_path_list;

}



        //Algoritmo A*
void Iatester::astar(node start, node goal, int opt)
{
    std::list<path> open_list;
    std::list<path> close_list;
    bool solution = false;

    path initial_path;
    initial_path.add(start.get_x(), start.get_y());

    float cost = heuristic(start.get_x(), start.get_y(), goal.get_x(), goal.get_y(), opt);

    initial_path.update_cost(cost);

    open_list.push_front(initial_path);


    int cont = 0;


    while((!open_list.empty()) && (!solution)){

        if((open_list.front().get_last_x() == goal.get_x()) && open_list.front().get_last_y() == goal.get_y())
            solution = true;
        else{
            path aux = (*open_list.begin()).get_path();

            open_list.pop_front();

            bool explore = false;

            explore = insert_path_close_list(close_list, aux);

            std::list<path> new_path_list;
            if(explore){
                find_new_paths(new_path_list, aux, opt);
            }
            for(std::list<path>::iterator list_iter = new_path_list.begin(); list_iter != new_path_list.end(); ++list_iter)
                insert_path_open_list(open_list, close_list, (*list_iter).get_path());

            sort_list(open_list);


        }


    }

    if(open_list.size() != 0){
        path solution_path = (*open_list.begin()).get_path();

        for(int i = 0; i < solution_path.get_size(); i++) {
            T.set_pos(solution_path[i].get_x(), solution_path[i].get_y(), 'Y');

            T.set_pos(solution_path[i-1].get_x(), solution_path[i-1].get_y(), '*');
            counter_p++;
            system("sleep 0.1");
            system("clear");
            T.write_map();
        }
        system("sleep 0.1");
        system("clear");
        std::cout << "\n\n";
        T.write_map();
    }

    else
    {
        std::cout << "No hay solución  \n";
    }

    std::cout << counter << '\n';
    std::cout << counter_p << '\n';

}


        //Inserta caminos en una lista secundaria
bool Iatester::insert_path_close_list(std::list<path>& close_list,path& path2) {

    bool exist = false;
    bool explore = false;

    int x_path = path2.get_last_x();
    int y_path = path2.get_last_y();
    int path_total_cost = path2.get_cost();

    int iter_total_cost = 0;

    for(std::list<path>::iterator list_iter = close_list.begin(); !exist && (list_iter != close_list.end()); list_iter++) {//Insertando la trayectoria en la lista cerrada
        if (((*list_iter).get_last_x() == x_path) && ((*list_iter).get_last_y() == y_path)) { //Detectando si es un camino similar
            exist = true;


            iter_total_cost = (*list_iter).get_cost();

            if (iter_total_cost > path_total_cost) {
                close_list.erase(list_iter);
                close_list.push_front(path2);
                explore = true;
            }

        }
    }
    if (!exist) {
        close_list.push_front(path2);
        explore = true;
    }

    return explore;
}


    //Lista principal, con el camino más rápido
void Iatester::insert_path_open_list(std::list<path>& open_list,std::list<path>& close_list,path path2)
{

    bool exist = false;

    int x_path = path2.get_last_x();
    int y_path = path2.get_last_y();
    int path_total_cost = path2.get_cost();

    int iter_total_cost = 0;

    for(std::list<path>::iterator list_iter = open_list.begin(); !exist && (list_iter != open_list.end()); list_iter++) {//Insertando la trayectoria en la lista cerrada
        if (((*list_iter).get_last_x() == x_path) && ((*list_iter).get_last_y() == y_path)) { //Detectando si es un camino similar
            exist = true;

            iter_total_cost = (*list_iter).get_cost();

            if (iter_total_cost > path_total_cost) {
                path aux;

                aux = (*list_iter).get_path();
                insert_path_close_list(close_list,aux);

                open_list.erase(list_iter);
                open_list.push_front(path2);
            }
        }
    }
    if (!exist) {
        open_list.push_front(path2);
    }



}


void Iatester::sort_list(std::list<path>& source_list) {

    if (source_list.size() != 0) {
        path min_path;

        min_path = (*source_list.begin()).get_path();
        int min_cost = min_path.get_cost();
        std::list<path>::iterator min_iter = source_list.begin();
        int iter_total_cost = 0;

        for(std::list<path>::iterator list_iter = source_list.begin(); list_iter != source_list.end(); list_iter++) {
            iter_total_cost = (*list_iter).get_cost();

                if (iter_total_cost < min_cost) {
                    min_path = (*list_iter).get_path();
                    min_cost = iter_total_cost;
                    min_iter = list_iter;
                }
        }

        source_list.erase(min_iter);

        source_list.push_front(min_path);
    }
}


void Iatester::astar_grafico(node start, node goal, int opt)
{
    std::list<path> open_list;
    std::list<path> close_list;
    bool solution = false;

    path initial_path;
    initial_path.add(start.get_x(), start.get_y());

    float cost = heuristic(start.get_x(), start.get_y(), goal.get_x(), goal.get_y(), opt);

    initial_path.update_cost(cost);

    open_list.push_front(initial_path);


    int cont = 0;


    while((!open_list.empty()) && (!solution)){

        if((open_list.front().get_last_x() == goal.get_x()) && open_list.front().get_last_y() == goal.get_y())
            solution = true;
        else{
            path aux = (*open_list.begin()).get_path();

            open_list.pop_front();

            bool explore = false;

            explore = insert_path_close_list(close_list, aux);

            std::list<path> new_path_list;
            if(explore){
                find_new_paths(new_path_list, aux, opt);
            }
            for(std::list<path>::iterator list_iter = new_path_list.begin(); list_iter != new_path_list.end(); ++list_iter)
                insert_path_open_list(open_list, close_list, (*list_iter).get_path());

            sort_list(open_list);


        }


    }

    if(open_list.size() != 0){
        path solution_path = (*open_list.begin()).get_path();

        for(int i = 0; i < solution_path.get_size(); i++) {
            T.set_pos(solution_path[i].get_x(), solution_path[i].get_y(), 'Y');

            T.set_pos(solution_path[i-1].get_x(), solution_path[i-1].get_y(), '*');
            counter_p++;
            system("sleep 1");
            T.write_map_grafico();
        }
        system("sleep 1");
        T.write_map_grafico();
    }

    else
    {
          printw("No hay solución");
    }

}
