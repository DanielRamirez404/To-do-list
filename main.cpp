#include "main.h"
#include "linked list.h"
#include "userinput.h"
#include "menu.h"
#include <iostream>
#include <string>
#include <functional>

void addTestingTasks(linkedList<const char*>& todoList) {
  todoList.append("Watch Oshi no Ko");
  todoList.append("Reread One Piece");
  todoList.preppend("Study kanji");
  todoList.preppend("(Keep) Play(ing) Stardew Valley");
  todoList.preppend("Finish to-do list");
  todoList.append("Make another website");
  todoList.append("Work on secret project");
  todoList.addByIndex(0, "Rework linkedLists");
  todoList.addByIndex(1, "Change to-do list examples");
  todoList.moveNode(5, 0);
  todoList.deleteByIndex(7);
  todoList.deleteByIndex(5);
  todoList.addByIndex(5, "Pratiquer l\'orthographie française");
}

void printx(int x) {
  std::cout << x;
}

void phoenixWrightFunction() {
  std::cout << "OBJECTION!!!!!\n";
}

int main() {
  menuFunction phoenix { &phoenixWrightFunction, "objection!!!"};
  menuFunction saaans { std::bind(&printx, 5), "print x"};
  menuFunction functions[] { phoenix, saaans };
  menu testmenu{"TO-DO LIST", 2, functions};
  testmenu.run();
  // linkedList<const char*> todoList;
  // addTestingTasks(todoList);
  // bool keepRunning{true};
  // while (keepRunning) {
  //   printMenu();
  //   getAndDoUserOption(todoList, keepRunning);
  //   pressAnyToContinue();
  // }
  return 0;
}

void getAndDoUserOption(linkedList<const char*>& todoList, bool& keepRunning) {
  int option { getUserInput<int>() };
  switch (option) {
    case 1:
      printTodoList(todoList);
      break;
    case 6:
      keepRunning = false;
      break;
    default:
      printBadInputError();
      break;
  }
}

void printTodoList(linkedList<const char*>& todoList) {
  for (size_t i{1}; todoList.iterate() !=  NULL; ++i) {
    std::cout << i << ") " << todoList.getIteratorValue() << '\n';
  }
}
