#include "main.h"
#include "linked list.h"
#include "userinput.h"
#include "userstring.h"
#include "menu.h"
#include <iostream>
#include <fstream>
#include <functional>
#include <string>

int main() {
  linkedList<const char*>* todoList { new linkedList<const char*> };
  std::string* readTasksHolder{};
  if (isThereLoadableData()) readSavedData(todoList, readTasksHolder);
  constexpr int numberOfFunctions{5};
  menu myMenu{"TO-DO LIST", numberOfFunctions, getTodoListFunctions(todoList, numberOfFunctions)};
  myMenu.run();
  saveTodoListData(todoList);
  delete todoList;
  return 0;
}

menuFunction* getTodoListFunctions(linkedList<const char*>* todoList, int numberOfFunctions) {
  menuFunction print { std::bind(&printTodoList, todoList), "CHECK TO-DO LIST" };
  menuFunction addOrDelete { std::bind(&addOrDeleteTasks, todoList), "ADD / ELIMINATE TASKS" };
  menuFunction modify { std::bind(&modifyTasks, todoList), "MODIFY TASK" };
  menuFunction relocate { std::bind(&relocateTasks, todoList), "RELOCATE TASK" };
  menuFunction eraseAll { std::bind(&eraseAllTasks, todoList), "ERASE ALL DATA" };
  menuFunction* functions { new menuFunction[numberOfFunctions] { print, addOrDelete, modify, relocate, eraseAll } };
  return functions;
}

void printTodoList(linkedList<const char*>* todoList) {
  for (size_t i{1}; todoList->iterate() !=  NULL; ++i) {
    std::cout << i << ") " << todoList->getIteratorValue() << '\n';
  }
}

void addOrDeleteTasks(linkedList<const char*>* todoList) {    // To do: asking which one and where
  for (size_t i{1}; todoList->iterate() !=  NULL; ++i) {
    std::cout << i << ") " << todoList->getIteratorValue() << '\n';
  }
}

void modifyTasks(linkedList<const char*>* todoList) {         // To do: get by index + Edit and Overwrite
  for (size_t i{1}; todoList->iterate() !=  NULL; ++i) {
    std::cout << i << ") " << todoList->getIteratorValue() << '\n';
  }
}

void relocateTasks(linkedList<const char*>* todoList) {       // To do: asking which one and where
  for (size_t i{1}; todoList->iterate() !=  NULL; ++i) {
    std::cout << i << ") " << todoList->getIteratorValue() << '\n';
  }
}

void eraseAllTasks(linkedList<const char*>* todoList) {       // To do: delete list and savefile 
  for (size_t i{1}; todoList->iterate() !=  NULL; ++i) {
    std::cout << i << ") " << todoList->getIteratorValue() << '\n';
  }
}

// Last 5 'for's are just to temporaly deactivate -werrors 

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

void readSavedData(linkedList<const char*>* todoList, std::string* readTasksHolder) {
  std::fstream textFile{"todolist.txt", std::ios::in};
  std::string textLine{};
  for (size_t i{0}; std::getline(textFile, textLine); ++i) {
    if (textLine[0] == '*') {
      readTasksHolder[todoList->getSize()] = getTextByCharLimits(textLine, '[', ']');
      todoList->append(readTasksHolder[todoList->getSize()].c_str());
    } else if (getWordInSentence(textLine, 1) == "Size:") {
      int readListSize{ std::stoi(getWordInSentence(textLine, 2)) };
      readTasksHolder = new std::string[readListSize];
    }
  }
  textFile.close();
}

void saveTodoListData(linkedList<const char*>* todoList) {
  remove("todolist.txt");
  std::fstream textFile{"todolist.txt", std::ios::out};
  if (todoList->isEmpty()) {
    textFile << "[NO DATA AVAILABLE]";
  } else {
    textFile << "[DATA AVAILABLE]";
    textFile << "\nSize: " << todoList->getSize();
    textFile << "\n<<< ---------------------------------------- >>>";
    while (todoList->iterate() != NULL) {
      textFile << "\n* [" << todoList->getIteratorValue() << ']';
    }
    textFile << "\n<<< ---------------------------------------- >>>";
  }
  textFile.close();
}
