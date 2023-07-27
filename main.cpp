#include "main.h"
#include "linked list.h"
#include "userinput.h"
#include "userstring.h"
#include "menu.h"
#include <iostream>
#include <fstream>
#include <functional>
#include <string>

namespace NumberOfFunctions {
  constexpr int todoList{5};
  constexpr int addOrDelete{2};
  constexpr int whereToAddOrDelete{3};
}

int main() {
  linkedList<std::string*>* todoList { new linkedList<std::string*> };
  if (isThereLoadableData()) readSavedData(todoList);
  menu todoListMenu{"TO-DO LIST", NumberOfFunctions::todoList, getTodoListFunctions(todoList)};
  todoListMenu.run();
  delete todoList;
  return 0;
}

menuFunction* getTodoListFunctions(linkedList<std::string*>* todoList) {
  menuFunction print { std::bind(&printTodoList, todoList), "CHECK TO-DO LIST" };
  menuFunction addOrDelete { std::bind(&addOrDeleteTasks, todoList), "ADD / DELETE TASK" };
  menuFunction modify { std::bind(&modifyTasks, todoList), "MODIFY TASK" };
  menuFunction relocate { std::bind(&relocateTasks, todoList), "RELOCATE TASK" };
  menuFunction eraseAll { std::bind(&eraseAllTasks, todoList), "ERASE ALL DATA" };
  menuFunction* functions { new menuFunction[5] { print, addOrDelete, modify, relocate, eraseAll } };
  return functions;
}

void printTodoList(linkedList<std::string*>* todoList) {
  if(todoList->isEmpty()) {
    std::cout << "OH-OH, SEEMS LIKE YOUR TO-DO LIST IS EMPTY!";
  } else {
    for (size_t i{1}; todoList->iterate() !=  NULL; ++i) {
      std::cout << i << ") " << *(todoList->getIteratorValue()) << '\n';
    }
  }
}

void addOrDeleteTasks(linkedList<std::string*>* todoList) {    // To do: asking which one and where
  menuFunction add { std::bind(&addTasks, todoList), "ADD TASK"};
  menuFunction eliminate { std::bind(&eliminateTasks, todoList), "DELETE TASK"};
  menuFunction* addOrDeletefunctions { new menuFunction[NumberOfFunctions::addOrDelete] {add, eliminate}}; 
  menu addOrDeleteMenu {"ADD / DELETE", NumberOfFunctions::addOrDelete, addOrDeletefunctions};
  addOrDeleteMenu.run();
  // saveTodoListData(todoList);
  // std::cout << "YOUR DATA HAS BEEN SUCEESSFULLY SAVED\n";
}

void addTasks(linkedList<std::string*>* todoList) {
  std::cout << "PLEASE, INPUT THE TASK YOU WANT TO ADD: \n";
  std::string* task{ new std::string { getUserInputLine() } };
  menuFunction preppend { std::bind(&linkedList<std::string*>::preppend, todoList, task), "ADD FIRST"};
  menuFunction append { std::bind(&linkedList<std::string*>::append, todoList, task), "ADD LAST"};
  menuFunction byIndex { std::bind(&addTaskByIndex,  todoList, task), "ADD BY INDEX"};
  menuFunction* addFunctions{ new menuFunction[NumberOfFunctions::whereToAddOrDelete] { preppend, append, byIndex} };
  menu add{ "ADD", NumberOfFunctions::whereToAddOrDelete, addFunctions};
  add.runOnce();
  std::cout << "YOUR TASK WAS SUCCESSFULLY ADDED!\n";
}

void addTaskByIndex(linkedList<std::string*>* todoList, std::string* task) {
  std::cout << "PLEASE, ENTER THE INDEX YOU WANT TO ADD THE TASK TO\n";
  size_t index{ getUserInput<size_t>() - 1 };
  todoList->addByIndex(index, task);
}

void eliminateTasks(linkedList<std::string*>* todoList) {
  menuFunction head { std::bind(&linkedList<std::string*>::deleteHead, todoList), "DELETE FIRST" };
  menuFunction tail { std::bind(&linkedList<std::string*>::deleteTail, todoList), "DELETE LAST" };
  menuFunction byIndex { std::bind(&eliminateTaskByIndex, todoList), "DELETE BY INDEX" };
  menuFunction* addFunctions{ new menuFunction[NumberOfFunctions::whereToAddOrDelete] { head, tail, byIndex} };
  menu add{ "DELETE", NumberOfFunctions::whereToAddOrDelete, addFunctions};
  add.runOnce();
}

void eliminateTaskByIndex(linkedList<std::string*>* todoList) {
  std::cout << "PLEASE, ENTER THE INDEX OF THE TASK YOU WANT TO DELETE\n";
  size_t index{ getUserInput<size_t>() - 1 };
  todoList->deleteByIndex(index);
}

void modifyTasks(linkedList<std::string*>* todoList) {         // To do: get by index + Edit and Overwrite
  for (size_t i{1}; todoList->iterate() !=  NULL; ++i) {
    std::cout << i << ") " << todoList->getIteratorValue() << '\n';
  }
}

void relocateTasks(linkedList<std::string*>* todoList) {       // To do: asking which one and where
  for (size_t i{1}; todoList->iterate() !=  NULL; ++i) {
    std::cout << i << ") " << todoList->getIteratorValue() << '\n';
  }
}

void eraseAllTasks(linkedList<std::string*>* todoList) {       // To do: delete list and savefile 
  for (size_t i{1}; todoList->iterate() !=  NULL; ++i) {
    std::cout << i << ") " << todoList->getIteratorValue() << '\n';
  }
}

// Last 4 'for's are just to temporaly deactivate -werrors 

bool isThereLoadableData() {
  std::fstream textFile{"todolist.txt", std::ios::in};
  std::string textLine{};
  bool isThereLoadableData{false};
  if (textFile.is_open()) {
      while (std::getline(textFile, textLine)) {
      isThereLoadableData = (textLine == "[DATA AVAILABLE]");
      break;
    }
  }
  textFile.close();
  return isThereLoadableData;
}

void readSavedData(linkedList<std::string*>* todoList) {
  std::fstream textFile{"todolist.txt", std::ios::in};
  std::string textLine{};
  for (size_t i{0}; std::getline(textFile, textLine); ++i) {
    if (textLine[0] == '*') {
      todoList->append(new std::string {getTextByCharLimits(textLine, '[', ']')} );
    }
  }
  textFile.close();
}

void saveTodoListData(linkedList<std::string*>* todoList) {
  remove("todolist.txt");
  std::fstream textFile{"todolist.txt", std::ios::out};
  if (todoList->isEmpty()) {
    textFile << "[NO DATA AVAILABLE]";
  } else {
    textFile << "[DATA AVAILABLE]";
    textFile << "\n<<< ---------------------------------------- >>>";
    while (todoList->iterate() != NULL) {
      textFile << "\n* [" << *(todoList->getIteratorValue()) << ']';
    }
    textFile << "\n<<< ---------------------------------------- >>>";
  }
  textFile.close();
}
