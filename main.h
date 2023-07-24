#ifndef MAIN
#define MAIN
#include "linked list.h"
#include "menu.h"

menuFunction* getTodoListFunctions(linkedList<const char*>* todoList);
void printTodoList(linkedList<const char*>* todoList);
void addOrDeleteTasks(linkedList<const char*>* todoList);
void modifyTasks(linkedList<const char*>* todoList);
void relocateTasks(linkedList<const char*>* todoList);
void eraseAllTasks(linkedList<const char*>* todoList);


#endif
