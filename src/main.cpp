#include <ncurses.h>
#include <vector>
#include <getopt.h>
#include <string>
#include "../include/iatester.hpp"
#include "../include/menu.hpp"
#include "../include/functions.hpp"


int main(int argc, char** argv){

  bool fromfile;

  if (argc == 1){
   PrintHelp();
   exit(0);
  }

  for (int i = 0; i < argc; ++i) {
    if(std::string(argv[i]) == "-f"){
      fromfile=true;
      break;
    }
  }

  std::vector<int> values = ProcessArgs(argc, argv);
  Iatester test(values, fromfile);
}
