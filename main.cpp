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
  while (todoList.iterate() !=  NULL) {
    std::cout << "* " << todoList.getIteratorValue() << '\n';
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
  for (size_t i = 0; i < todoList.getSize(); i++) {
    std::cout << i + 1 << "- " << todoList[i] << '\n';  //this is actually slower than just iterating and printing, but I wanted to try this for readability, just as if it were an array
  }
}
