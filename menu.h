#ifndef MENU
#define MENU
#include <functional>
#include <string>

struct menuFunction {
  std::function<void()> function;
  std::string name;
};

class menu {
protected:
  std::string exitMessage{"GO BACK"};
  std::string title{};
  int totalOptions{};
  menuFunction* functions{};
  bool isUserQuitting(int selectedOption) { return (selectedOption == totalOptions + 1); };
  bool isQuittingConfirmed();
  void printTitle();
public:
  menu (const menu&) = delete;
  menu& operator=(const menu&) = delete; 
  menu(std::string menuTitle, int totalFunctions, menuFunction* menuFunctions);
  ~menu() { delete[] functions; };
  void run();
  void print();
};

class mainMenu : public menu {
public:
  mainMenu(std::string menuTitle, int totalFunctions, menuFunction* menuFunctions) : menu (menuTitle, totalFunctions, menuFunctions) { menu::exitMessage = "EXIT"; };
};

class runOnceMenu : public menu {
public:
  void run();
  using menu::menu;
};

#endif
