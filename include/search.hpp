#include <vector>

#include "map_t.hpp"
#include "node_t.hpp"

struct point_t
{
  int x;
  int y;
};


class search
{
  private:
    std::vector<node_t*> c_list;
    std::vector<node_t*> a_list;
    std::vector<point_t> best_path;
    map_t* map_;

  public:
    search(map_t *map);
    ~search(void);
    std::vector<point_t> search(int s_x, int s_y, int e_x, int e_y);

  private:
    void add_node_a_list(node_t* node);
    bool contain_c_list(node_t* node) const;
    bool contain_a_list(node_t* node) const;
    std::vector<node_t*> search_adjacent_nodes(node_t* current, node_t* end) const;
};
