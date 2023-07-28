#include "menu.h"
#include "userinput.h"
#include <iostream>
#include <string>
#include <cassert>
#include <functional>

menu::menu(std::string menuTitle, int totalFunctions, menuFunction* menuFunctions) {
  title = menuTitle;
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

bool menu::isQuittingConfirmed() {
  std::cout << "ARE YOU SURE YOU WANT TO " << exitMessage << "? (y/n)\n";
  return ynInput();
}

void menu::print() {
  printTitle();
  for (int i{0}; i < totalOptions; ++i) {
    std::cout << i + 1 << ") " << functions[i].name << '\n'; 
  }
  std::cout << totalOptions + 1 << ") " << exitMessage << '\n';
}

void menu::printTitle() {
  constexpr int menuWidth{46};
  constexpr int halfWidth{menuWidth / 2};
  const int titleSize { static_cast<int>(title.size()) };
  const int halfTitleSize{titleSize / 2};
  assert((titleSize <= menuWidth) && "THE TITLE CAN\'T BE TOO LONG");
  std::cout << "----------------------------------------------\n";
  std::string centeredTitle{""};
  for (int i{0}; i < halfWidth - halfTitleSize; i++) {
    centeredTitle.append(" ");
  }
  centeredTitle.append(title);
  std::cout << centeredTitle << '\n';
  std::cout << "----------------------------------------------\n";
}

void runOnceMenu::run() {
  print();
  int selectedOption{ getUserInput<int>() };
  assert((selectedOption > 0) && (selectedOption <= totalOptions + 1) && "Nonvalid option");
  if (isUserQuitting(selectedOption)) {
    if (!isQuittingConfirmed()) {
      run();
    }
  } else {
    functions[selectedOption - 1].function();
  }
}
