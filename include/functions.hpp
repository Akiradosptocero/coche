#include <vector>
#include <iostream>

#define DEFAULT_PROB    5
#define DEFAULT_WIDTH   50
#define DEFAULT_HEIGHT  50


void PrintHelp()
{
    std::cout <<
             "Uso:\n"
             "  -d : Modo por defecto\n"
             "  -g : Modo gráfico\n"
             "  -w : Ancho. [Default: 50]\n"
             "  -h : Alto.  [Default: 50]\n"
             "  -p : Probabilidad bloques.  [Default: 5] \n"
             "  -f : Archivo preconfigurado\n";
             "  -a : Funcion heuristica. [1,2,3]";
    exit(0);
}


std::vector<int> ProcessArgs(int argc, char** argv){

    const char* const short_opts = "dgw:h:p:fa:";

    int opt = 0, index = 0;
    std::vector<int> valores(5);

    while ((opt = getopt(argc, argv, short_opts)) != -1)
    {
        if (-1 == opt)
            break;
        else if (opt == 'd')
            break;

        switch (opt)
        {
        case 'g':
            valores[3]=1;
            break;

        case 'p':
            valores[0]=atoi(optarg);
            break;

        case 'w':
            valores[1]=atoi(optarg);
            break;

        case 'h':
            valores[2]=atoi(optarg);
            break;
        case 'f':
            break;
        case 'a':
            valores[4]=atoi(optarg);
            break;

        case '?':
            PrintHelp();
            exit(0);

        default:
          std::fprintf(stderr, "Error 0%o en get_ops\n", opt);
          exit(0);
        }
    }

    if (valores[0]==0)
      valores[0]=DEFAULT_PROB;
    if (valores[1]==0)
      valores[1]=DEFAULT_WIDTH;
    if (valores[2]==0)
      valores[2]=DEFAULT_HEIGHT;
    if (valores[4]==0)
      valores[0]==1;

    return valores;

}
