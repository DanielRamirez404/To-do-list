#include "menu.h"
#include "userinput.h"
#include <iostream>
#include <cassert>
#include <functional>

menu::menu(const char* menuName, int totalFunctions, menuFunction* menuFunctions) {
  name = menuName;
  totalOptions = totalFunctions;
  functions = menuFunctions;
}

void menu::run() {
  while (true) {
    print();
    int selectedOption{ getUserInput<int>() };
    assert((selectedOption > 0) && (selectedOption <= totalOptions + 1) && "Nonvalid option");
    if (isUserQuitting(selectedOption)) { 
      if (isQuittingConfirmed()) {
        break;
      } else {
        continue;
      }
    }
    functions[selectedOption - 1].function();
    pressAnyToContinue();
  }
}

bool menu::isUserQuitting(int selectedOption) {
  return (selectedOption == totalOptions + 1);
}

bool menu::isQuittingConfirmed() {
  std::cout << "ARE YOU SURE YOU WANT TO GO BACK? (y/n)\n";
  return ynInput();
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
