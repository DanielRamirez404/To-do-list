#ifndef MAIN
#define MAIN
#include "linked list.h"
#include "menu.h"
#include <string>
#include <vector>

std::vector<menuFunction> getTodoListFunctions(linkedList<std::string>& todoList);
void printTodoList(linkedList<std::string>* todoList);
void addOrDeleteTasks(linkedList<std::string>* todoList);
void addTasks(linkedList<std::string>* todoList);
void addTaskByIndex(linkedList<std::string>* todoList, std::string task);
void eliminateTasks(linkedList<std::string>* todoList);
void eliminateTaskByIndex(linkedList<std::string>* todoList);
void modifyTasks(linkedList<std::string>* todoList);
void relocateTasks(linkedList<std::string>* todoList);
void eraseAllTasks(linkedList<std::string>* todoList);
bool isThereLoadableData();
void readSavedData(linkedList<std::string>& todoList);
void saveTodoListData(linkedList<std::string>& todoList);


#endif
