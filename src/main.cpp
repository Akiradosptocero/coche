#include <ncurses.h>
#include <vector>
#include <getopt.h>
#include <string>
#include "iatester.hpp"
#include "menu.hpp"
#include "functions.hpp"


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
