#ifndef MAIN
#define MAIN
#include "linked list.h"
#include "menu.h"
#include <string>
#include <vector>

std::vector<menuFunction> getTodoListFunctions(linkedList<std::string>& todoList);
void printTodoList(linkedList<std::string>* todoList);
void addOrDeleteTask(linkedList<std::string>* todoList);
void addTask(linkedList<std::string>* todoList);
void addTaskByIndex(linkedList<std::string>* todoList, std::string& task);
void eliminateTask(linkedList<std::string>* todoList);
void eliminateTaskByIndex(linkedList<std::string>* todoList);
void overwriteTask(linkedList<std::string>* todoList);
void moveTask(linkedList<std::string>* todoList);
void moveTaskToIndex(linkedList<std::string>* todoList, size_t& oldIndex);
void eraseAllTask(linkedList<std::string>* todoList);


#endif
