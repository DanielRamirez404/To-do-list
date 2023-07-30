#ifndef MENU
#define MENU
#include <cstddef>
#include <functional>
#include <string>
#include <vector>

struct menuFunction {
  std::function<void()> function;
  std::string name;
};

class menu {
protected:
  std::string exitMessage{"GO BACK"};
  std::string title{};
  size_t totalOptions{};
  std::vector<menuFunction> functions{};
  bool isUserQuitting(size_t selectedOption) { return (selectedOption == totalOptions + 1); };
  bool isQuittingConfirmed();
  void printTitle();
public:
  menu (const menu&) = delete;
  menu& operator=(const menu&) = delete; 
  menu(std::string menuTitle, std::vector<menuFunction> menuFunctions);
  void run();
  void print();
};

class mainMenu : public menu {
public:
  mainMenu(std::string menuTitle, std::vector<menuFunction> menuFunctions) : menu (menuTitle, menuFunctions) { menu::exitMessage = "EXIT"; };
};

class runOnceMenu : public menu {
public:
  void run();
  using menu::menu;
};

#endif
