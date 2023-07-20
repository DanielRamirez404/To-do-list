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
  int taskCounter{1};
  while (todoList.iterate() !=  NULL) {
    std::cout << taskCounter << "- " << todoList.getIteratorValue() << '\n';
    taskCounter++;
  }
  todoList.resetIterator();
}
