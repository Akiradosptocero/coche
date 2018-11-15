#include <curses.h>
#include <locale.h>
#include <string.h>
#include <vector>

using namespace std;

class Menu {

  private:
    vector<int> opciones;
    bool start;
  public:

    Menu();
    ~Menu();
    bool get_start();
    vector<int> get_opciones();

    int n_chars (char *str);
    void str_cp (char *dest, char *src);

    void generate();
    int print_menu (int sty, int x, int alts, int width, char title[], char entries[][100], int start);



};
