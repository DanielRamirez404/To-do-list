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
  bool isUserQuitting(int selectedOption);
  bool isQuittingConfirmed();
  void printExitMessage();
public:
  menu(const char* menuName, int totalFunctions, menuFunction* menuFunctions);
  void run();
  void print();
};

#endif
