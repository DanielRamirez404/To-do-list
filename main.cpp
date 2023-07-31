#include "to-do list.h"
#include "to-do list fstream.h"
#include "menu.h"
#include "linked list.h"
#include <iostream>
#include <string>

int main() {
  linkedList<std::string> todoList;
  if (isThereLoadableData()) readSavedData(todoList);
  mainMenu todoListMenu{ "TO-DO LIST", getTodoListFunctions(todoList) };
  todoListMenu.run();
  saveTodoListData(todoList);
  std::cout << "YOUR DATA HAS BEEN SUCEESSFULLY SAVED\n";
  std::cout << "SEE YOU NEXT TIME!\n\n";
  return 0;
}
