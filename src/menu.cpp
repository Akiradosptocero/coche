#include "../include/menu.hpp"

Menu::Menu(): opciones(1,1), start(0) {

  generate();

}

Menu::~Menu(){}

bool Menu::get_start(){ return start; }
vector<int> Menu::get_opciones(){ return opciones; }

void Menu::generate(){


      int menu_ret = 1;

      char alts[][100] =  {{"Start Game"},
  			                   {"Modo"},
                           {"Quit Game"}};
      char alts2[][100] = {{"Manual"},
                           {"Automatico"}};

      setlocale (LC_CTYPE, "");

      initscr();
      noecho();
      keypad (stdscr, TRUE);
      meta (stdscr, TRUE);
      nodelay (stdscr, FALSE);
      notimeout (stdscr, TRUE);
      raw();
      curs_set (0);

do {

  	char title[]= "MAIN MENU";
  	char title2[] = "SELECT SLOT";
          menu_ret = print_menu (2, 3, 3, 15, title, alts, menu_ret);


  	if (menu_ret == 1){

      start = true;

  		mvprintw (5, 23, "Devolviendo las opciones seleccionadas.");
              	mvprintw (6, 26, "Presione cualquier tecla para seguir.");
              	getch();


  	           }
          else if (menu_ret == 2) {

        	    do {

                        opciones[0] = print_menu (6, 22, 2, 15, title2, alts2, 1);

              }while ((opciones[0] != 1) && (opciones[0] != 2));


          }

          else if(menu_ret == 3)
            start = false;



          erase();
      }
      while (menu_ret != 3 && menu_ret != 1);

      endwin();


}

int Menu::n_chars (char *str) {

    int i = 0;

    while (1){

        if (*(str + i++) == '\0')
            return --i;
    }
}


void Menu::str_cp (char *dest, char *src){

    int i = 0;

    do {
        if (*(src + i) != '\0') {

            *(dest + i) = *(src + i);
            i++;
        }
    }
    while (*(src + i) != '\0');

    *(dest + i) = '\0';


}


int Menu::print_menu (int sty, int x, int alts, int width, char title[], char entries[][100], int start){

    int i, j, k, blankspace1, blankspace2, currow = start, y = sty, key;
    char temparray[100];

    if (n_chars (title) + 2 > width)
        width = n_chars (title) + 2;

    for (k = 0; k < alts; k++)
    {
        if (n_chars (&entries[k][0]) + 2 > width)
            width = n_chars (&entries[k][0]) + 2;
    }

    k = 0;
    move (y++, x);
    addch (ACS_ULCORNER);

    for (i = 0; i < width; i++)
        addch (ACS_HLINE);

    addch (ACS_URCORNER);
    printw ("\n");
    move (y++, x);

    if ((width - n_chars (title)) % 2 != 0)
    {
        blankspace2 = (width - n_chars (title) + 1) / 2;
        blankspace1 = blankspace2 - 1;
    }

    else
    {
        blankspace1 = (width - n_chars (title)) / 2;
        blankspace2 = blankspace1;
    }

    addch (ACS_VLINE);

    for (i = 0; i < blankspace1; i++)
        printw (" ");

    printw ("%s", title);

    for (i = 0; i < blankspace2; i++)
        printw (" ");

    addch (ACS_VLINE);
    printw ("\n");
    move (y++, x);
    addch (ACS_LTEE);

    for (i = 0; i < width; i++)
        addch (ACS_HLINE);

    addch (ACS_RTEE);
    printw ("\n");
    move (y++, x);

    for (j = 0; j < alts - 1; j++)
    {
        addch (ACS_VLINE);
        printw (" %s", &entries[k][0]);
        blankspace1 = width - (n_chars (&entries[k][0]) + 1);

        for (i = 0; i < blankspace1; i++)
            printw(" ");

        k++;
        addch (ACS_VLINE);
        printw ("\n");
        move (y++, x);
        addch (ACS_LTEE);

        for (i = 0; i < width; i++)
            addch (ACS_HLINE);

        addch (ACS_RTEE);
        printw ("\n");
        move (y++, x);
    }

    addch (ACS_VLINE);
    printw (" %s", &entries[k][0]);
    blankspace1 = width - (n_chars (&entries[k][0]) + 1);

    for (i = 0; i < blankspace1; i++)
        printw(" ");

    k++;
    addch (ACS_VLINE);
    printw ("\n");
    move (y++, x);
    addch (ACS_LLCORNER);

    for (i = 0; i < width; i++)
        addch (ACS_HLINE);

    addch (ACS_LRCORNER);
    printw ("\n");

    do
    {
        attron (A_STANDOUT);
        blankspace1 = width - (n_chars (&entries[currow - 1][0]) + 1);
        temparray[0] = ' ';
        str_cp (&temparray[1], &entries[currow - 1][0]);

        for (i = n_chars (&entries[currow - 1][0]) + 1; i < width; i++)
        {
            temparray[i] = ' ';
        }

        temparray[i] = '\0';
        mvprintw ((sty + 3) + (currow - 1) * 2, x + 1, "%s", temparray);
        attroff (A_STANDOUT);
        key = getch();

        if (key == KEY_UP)
        {
            mvprintw ((sty + 3) + (currow - 1) * 2,
                      x + 1, "%s", temparray);

            if (currow == 1)
                currow = alts;

            else
                currow--;
        }

        else if (key == KEY_DOWN)
        {
            mvprintw ((sty + 3) + (currow - 1) * 2,
                      x + 1, "%s", temparray);

            if (currow == alts)
                currow = 1;

            else
                currow++;
        }
    }
    while (key != '\n' && key != '\r' && key != 459);

    return currow;
}
