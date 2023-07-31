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
  saveTodoListData(todoList);
  std::cout << "YOUR DATA HAS BEEN SUCEESSFULLY SAVED\n";
  std::cout << "SEE YOU NEXT TIME!\n";
  return 0;
}

std::vector<menuFunction> getTodoListFunctions(linkedList<std::string>& todoList) {
  std::vector<menuFunction> functions{};
  functions.push_back( { std::bind(&printTodoList, &todoList), "CHECK TO-DO LIST" } );
  functions.push_back( { std::bind(&addOrDeleteTask, &todoList), "ADD / DELETE TASK" } );
  functions.push_back( { std::bind(&overwriteTask, &todoList), "OVERWRITE TASK" } );
  functions.push_back( { std::bind(&moveTask, &todoList), "RELOCATE TASK" } );
  functions.push_back( { std::bind(&eraseAllTask, &todoList), "ERASE ALL DATA" } );
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

void addOrDeleteTask(linkedList<std::string>* todoList) {
  std::vector<menuFunction> addOrDeletefunctions{};
  addOrDeletefunctions.push_back( { std::bind(&addTask, todoList), "ADD TASK" } );
  addOrDeletefunctions.push_back( { std::bind(&eliminateTask, todoList), "DELETE TASK" } );
  menu addOrDeleteMenu {"ADD / DELETE", addOrDeletefunctions};
  addOrDeleteMenu.run();
}

void addTask(linkedList<std::string>* todoList) {
  std::cout << "PLEASE, INPUT THE TASK YOU WANT TO ADD:\n";
  std::string task { getUserInputLine() };
  std::vector<menuFunction> addFunctions{};
  addFunctions.push_back( { std::bind(&linkedList<std::string>::preppend, todoList, task), "ADD FIRST" } );
  addFunctions.push_back( { std::bind(&linkedList<std::string>::append, todoList, task), "ADD LAST"} );
  addFunctions.push_back( { std::bind(&addTaskByIndex, todoList, task), "ADD BY INDEX" } );
  runOnceMenu add{ "ADD", addFunctions};
  add.run();
}

void addTaskByIndex(linkedList<std::string>* todoList, std::string& task) {
  std::cout << "PLEASE, ENTER THE INDEX YOU WANT TO ADD THE TASK TO\n";
  size_t index{ getUserInput<size_t>() - 1 };
  todoList->addByIndex(index, task);
}

void eliminateTask(linkedList<std::string>* todoList) {
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

void overwriteTask(linkedList<std::string>* todoList) {         
  std::cout << "PLEASE, ENTER THE INDEX OF YOUR DESIRED TASK\n";
  size_t index{ getUserInput<size_t>() - 1 };
  std::cout << "DO YOU WANT TO OVERWRITE THIS TASK?: (y/n)\n";
  std::cout << "TASK: " << (*todoList)[index] << '\n';
  if (ynInput()) {
      std::cout << "THEN, ENTER YOUR WISHED TEXT\n";
      std::string task { getUserInputLine() };
      todoList->overwriteValue(index, task);
      std::cout << "YOUR TASK WAS SUCCESSFULLY OVERWRITTEN\n";
  }
}

void moveTask(linkedList<std::string>* todoList) {  // To do: asking which one and where
  std::cout << "PLEASE, ENTER THE INDEX OF YOUR DESIRED TASK\n";
  size_t oldIndex{ getUserInput<size_t>() - 1 };
  std::cout << "DO YOU WANT TO MOVE THIS TASK?: (y/n)\n";
  std::cout << "TASK: " << (*todoList)[oldIndex] << '\n';
  if (ynInput()) {
    std::cout << "THEN, ENTER YOUR PREFERED OPTION\n";
    std::cout << "TO MOVE THE TASK TO\n";
    std::vector<menuFunction> moveFunctions{};
    moveFunctions.push_back( { std::bind(&linkedList<std::string>::moveNodeToHead, todoList, oldIndex), "MOVE TO FIRST" } );
    moveFunctions.push_back( { std::bind(&linkedList<std::string>::moveNodeToTail, todoList, oldIndex), "MOVE TO LAST" } );
    moveFunctions.push_back( { std::bind(&moveTaskToIndex, todoList, oldIndex), "MOVE TO INDEX" } );
    runOnceMenu move{"MOVE", moveFunctions};
    move.run();
  }
}

void moveTaskToIndex(linkedList<std::string>* todoList, size_t& oldIndex) {
  std::cout << "ENTER THE INDEX YOU WANT TO MOVE THE TASK TO\n";
  size_t newIndex{ getUserInput<size_t>() - 1 };
  todoList->moveNode(oldIndex, newIndex);
}

void eraseAllTask(linkedList<std::string>* todoList) {       
  // To do: delete list and savefile
  printTodoList(todoList);
}

// Last 'printTodoList' is just to temporaly deactivate -werrors
