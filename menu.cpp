#include "menu.h"
#include "userinput.h"

#include <cassert>
#include <cstddef>
#include <iostream>
#include <functional>
#include <string>
#include <vector>

menu::menu(std::string menuTitle, std::vector<menuFunction> menuFunctions) {
  title = menuTitle;
  functions = menuFunctions;
  totalOptions = menuFunctions.size();
}

void menu::run() {
  while (true) {
    clearConsole();
    print();
    size_t selectedOption{ getUserInput<size_t>() };
    assert((selectedOption > 0) && (selectedOption <= totalOptions + 1) && "Nonvalid option");
    if (isUserQuitting(selectedOption)) { 
      if (isQuittingConfirmed()) {
        break;
      } else {
        continue;
      }
    }
    functions[static_cast<size_t>(selectedOption - 1)].function();
    pressAnyToContinue();
  }
}

bool menu::isQuittingConfirmed() {
  std::cout << "ARE YOU SURE YOU WANT TO " << exitMessage << "? (y/n)\n";
  return ynInput();
}

void menu::print() {
  printTitle();
  for (size_t i{0}; i < totalOptions; ++i) {
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
  size_t selectedOption{ getUserInput<size_t>() };
  assert((selectedOption > 0) && (selectedOption <= totalOptions + 1) && "Nonvalid option");
  if (isUserQuitting(selectedOption)) {
    if (isQuittingConfirmed()) {
      didUserQuit = true;
    } else {
      run();
    }
  } else {
    functions[static_cast<size_t>(selectedOption - 1)].function();
  }
}
