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
  std::string name{};
  int totalOptions{};
  menuFunction* functions{};
  bool isUserQuitting(int selectedOption);
  bool isQuittingConfirmed();
public:
  menu (const menu&) = delete;
  menu& operator=(const menu&) = delete; 
  menu(std::string menuName, int totalFunctions, menuFunction* menuFunctions);
  ~menu();
  void run();
  void print();
};

class mainMenu : public menu {
public:
  mainMenu(std::string menuName, int totalFunctions, menuFunction* menuFunctions) : menu (menuName, totalFunctions, menuFunctions) { menu::exitMessage = "EXIT"; };
};

class runOnceMenu : public menu {
public:
  void run();
  using menu::menu;
};

#endif
