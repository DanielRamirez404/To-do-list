#include "main.h"
#include "linked list.h"
#include "to-do list fstream.h"
#include "menu.h"
#include "userinput.h"

#include <iostream>
#include <functional>
#include <string>
#include <vector>

int main() {
  linkedList<std::string> todoList;
  if (isThereLoadableData()) readSavedData(todoList);
  std::vector<menuFunction> functions{ getTodoListFunctions(todoList) };
  mainMenu todoListMenu{ "TO-DO LIST", functions };
  todoListMenu.run();
  return 0;
}

std::vector<menuFunction> getTodoListFunctions(linkedList<std::string>& todoList) {
  std::vector<menuFunction> functions{};
  functions.push_back( { std::bind(&printTodoList, &todoList), "CHECK TO-DO LIST" } );
  functions.push_back( { std::bind(&addOrDeleteTasks, &todoList), "ADD / DELETE TASK" } );
  functions.push_back( { std::bind(&modifyTasks, &todoList), "MODIFY TASK" } );
  functions.push_back( { std::bind(&relocateTasks, &todoList), "RELOCATE TASK" } );
  functions.push_back( { std::bind(&eraseAllTasks, &todoList), "ERASE ALL DATA" } );
  return functions;
}

void printTodoList(linkedList<std::string>* todoList) {
  if(todoList->isEmpty()) {
    std::cout << "OH-OH, SEEMS LIKE YOUR TO-DO LIST IS EMPTY!\n";
  } else {
    for (size_t i{1}; todoList->iterate() !=  nullptr; ++i) {
      std::cout << i << ") " << (todoList->getIteratorValue()) << '\n';
    }
  }
}

void addOrDeleteTasks(linkedList<std::string>* todoList) {
  std::vector<menuFunction> addOrDeletefunctions{};
  addOrDeletefunctions.push_back( { std::bind(&addTasks, todoList), "ADD TASK" } );
  addOrDeletefunctions.push_back( { std::bind(&eliminateTasks, todoList), "DELETE TASK" } );
  menu addOrDeleteMenu {"ADD / DELETE", addOrDeletefunctions};
  addOrDeleteMenu.run();
  saveTodoListData(*todoList);
  std::cout << "YOUR DATA HAS BEEN SUCEESSFULLY SAVED\n";
}

void addTasks(linkedList<std::string>* todoList) {
  std::cout << "PLEASE, INPUT THE TASK YOU WANT TO ADD: \n";
  std::string task { getUserInputLine() };
  std::vector<menuFunction> addFunctions{};
  addFunctions.push_back( { std::bind(&linkedList<std::string>::preppend, todoList, task), "ADD FIRST" } );
  addFunctions.push_back( { std::bind(&linkedList<std::string>::append, todoList, task), "ADD LAST"} );
  addFunctions.push_back( { std::bind(&addTaskByIndex, todoList, task), "ADD BY INDEX" } );
  runOnceMenu add{ "ADD", addFunctions};
  add.run();
}

void addTaskByIndex(linkedList<std::string>* todoList, std::string task) {
  std::cout << "PLEASE, ENTER THE INDEX YOU WANT TO ADD THE TASK TO\n";
  size_t index{ getUserInput<size_t>() - 1 };
  todoList->addByIndex(index, task);
}

void eliminateTasks(linkedList<std::string>* todoList) {
  std::vector<menuFunction> deleteFunctions{};
  deleteFunctions.push_back( { std::bind(&linkedList<std::string>::deleteHead, todoList), "DELETE FIRST" } );
  deleteFunctions.push_back( { std::bind(&linkedList<std::string>::deleteTail, todoList), "DELETE LAST"} );
  deleteFunctions.push_back( { std::bind(&eliminateTaskByIndex, todoList), "DELETE BY INDEX" } );
  runOnceMenu eliminate{ "DELETE", deleteFunctions};
  eliminate.run();
}

void eliminateTaskByIndex(linkedList<std::string>* todoList) {
  std::cout << "PLEASE, ENTER THE INDEX OF THE TASK YOU WANT TO DELETE\n";
  size_t index{ getUserInput<size_t>() - 1 };
  todoList->deleteByIndex(index);
}

void modifyTasks(linkedList<std::string>* todoList) {         
  // To do: get by index + Edit and Overwrite
  printTodoList(todoList);
}

void relocateTasks(linkedList<std::string>* todoList) {       
  // To do: asking which one and where
  printTodoList(todoList);
}

void eraseAllTasks(linkedList<std::string>* todoList) {       
  // To do: delete list and savefile 
  printTodoList(todoList);
}

// Last 3 'printTodoList's are just to temporaly deactivate -werrors
