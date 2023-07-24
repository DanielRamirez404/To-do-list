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

int main() {
  linkedList<const char*>* todoList { new linkedList<const char*> };
  addTestingTasks(*todoList);
  menuFunction* functions { getTodoListFunctions(todoList) };
  menu myMenu{"TO-DO LIST", 5, functions};
  myMenu.run();
  return 0;
}

menuFunction* getTodoListFunctions(linkedList<const char*>* todoList) {
  menuFunction print { std::bind(&printTodoList, todoList), "CHECK TO-DO LIST" };
  menuFunction addOrDelete { std::bind(&addOrDeleteTasks, todoList), "ADD / ELIMINATE TASKS" };
  menuFunction modify { std::bind(&modifyTasks, todoList), "MODIFY TASK" };
  menuFunction relocate { std::bind(&relocateTasks, todoList), "RELOCATE TASK" };
  menuFunction eraseAll { std::bind(&eraseAllTasks, todoList), "ERASE ALL DATA" };
  menuFunction* functions { new menuFunction[5] { print, addOrDelete, modify, relocate, eraseAll } };
  return functions;
}

void printTodoList(linkedList<const char*>* todoList) {
  for (size_t i{1}; (*todoList).iterate() !=  NULL; ++i) {
    std::cout << i << ") " << (*todoList).getIteratorValue() << '\n';
  }
}

void addOrDeleteTasks(linkedList<const char*>* todoList) {    // asking which one and where
  for (size_t i{1}; (*todoList).iterate() !=  NULL; ++i) {
    std::cout << i << ") " << (*todoList).getIteratorValue() << '\n';
  }
}

void modifyTasks(linkedList<const char*>* todoList) {         // get by index + Edit and Overwrite
  for (size_t i{1}; (*todoList).iterate() !=  NULL; ++i) {
    std::cout << i << ") " << (*todoList).getIteratorValue() << '\n';
  }
}

void relocateTasks(linkedList<const char*>* todoList) {       // asking which one and where
  for (size_t i{1}; (*todoList).iterate() !=  NULL; ++i) {
    std::cout << i << ") " << (*todoList).getIteratorValue() << '\n';
  }
}

void eraseAllTasks(linkedList<const char*>* todoList) {       // delete list and savefile 
  for (size_t i{1}; (*todoList).iterate() !=  NULL; ++i) {
    std::cout << i << ") " << (*todoList).getIteratorValue() << '\n';
  }
}

// Last 4 'for's are just to temporaly deactivate -werrors 
