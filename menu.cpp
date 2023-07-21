#include "menu.h"
#include <iostream>

void printMenu() {
  std::cout << "----------------------------------------------\n";
  std::cout << "                 TO-DO LIST\n";
  std::cout << "----------------------------------------------\n";
  std::cout << "1) CHECK TO-DO LIST\n";       //Ok for the moment
  std::cout << "2) ADD NEW TASK\n";           //Needs rework before implementation
  std::cout << "3) ELIMINATE TASK\n";         //Not implemented
  std::cout << "4) CHANGE TASK POSITION\n";   //Not implemented
  std::cout << "5) RESET TO-DO LIST\n";       //Not implemented
  std::cout << "6) EXIT\n";                   //Ok for the moment
}
