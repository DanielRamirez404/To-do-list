#include "menu.h"
#include "userinput.h"
#include <iostream>
#include <functional>

menu::menu(const char* menuName, int totalFunctions, menuFunction* menuFunctions) {
  name = menuName;
  totalOptions = totalFunctions;
  functions = menuFunctions;
}

void menu::run() {
  while (true) {
    print();
    selectedOption = getUserInput<int>();
    if (doesUserWantToQuit()) { 
      break; 
    } 
    functions[selectedOption - 1].function();
    pressAnyToContinue();
  }
}

void menu::print() {
  std::cout << "----------------------------------------------\n";
  std::cout << name << '\n';
  std::cout << "----------------------------------------------\n";
  for (int i{0}; i < totalOptions; ++i) {
    std::cout << i + 1 << ") " << functions[i].name << '\n'; 
  }
  std::cout << totalOptions + 1 << ") GO BACK\n"; 
}

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
