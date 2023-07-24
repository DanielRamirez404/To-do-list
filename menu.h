#ifndef MENU
#define MENU
#include <functional>

struct menuFunction {
  std::function<void()> function;
  const char* name;
};

class menu {
private:
  const char* name{};
  int totalOptions{};
  menuFunction* functions{};
  int selectedOption{};
  bool doesUserWantToQuit() { return (selectedOption == totalOptions); };
public:
  menu(const char* menuName, int totalFunctions, menuFunction* menuFunctions);
  void run();
  void print();
};

void printMenu();

#endif
