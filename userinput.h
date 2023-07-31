#ifndef USER_INPUT
#define USER_INPUT
#include <iostream>
#include <string>

template <typename T> T getUserInput() {
  std::cout << "----------------------------------------------\n";
  std::cout << "INPUT: ";
  T userInput{};
  std::cin >> userInput;
  std::cout << "----------------------------------------------\n";
  return userInput;
}

std::string getUserInputLine();
bool ynInput();
void printBadInputError();
void pressAnyToContinue();
void clearConsole();

#endif
