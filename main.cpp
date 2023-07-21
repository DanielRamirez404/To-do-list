#include "main.h"
#include "linked list.h"
#include "userinput.h"
#include "menu.h"
#include <iostream>
#include <string>
#include <string_view>

void addTestingTasks(linkedList<const char*>& todoList) {
  todoList.append("Watch Oshi no Ko");
  todoList.append("Reread One Piece");
  todoList.preppend("Study kanji");
  todoList.preppend("(Keep) Play(ing) Stardew Valley");
  todoList.preppend("Finish to-do list");
  todoList.append("Make another website");
  todoList.append("Work on secret project");
  todoList.addValueByIndex(0, "Rework LinkedLists");
  todoList.addValueByIndex(1, "Change To-do list examples");
}

int main() {
  linkedList<const char*> todoList;
  addTestingTasks(todoList);
  bool keepRunning{true};
  while (keepRunning) {
    printMenu();
    getAndDoUserOption(todoList, keepRunning);
    pressAnyToContinue();
  }
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
  int i{1};
  while (todoList.iterate() !=  NULL) {
    std::cout << i << ") " << todoList.getIteratorValue() << '\n';
  }
}
