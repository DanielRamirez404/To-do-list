#ifndef TODO_LIST_FSTREAM
#define TODO_LIST_FSTREAM
#include "linked list.h"
#include <string>

bool isThereLoadableData();
void readSavedData(linkedList<std::string>& todoList);
void saveTodoListData(linkedList<std::string>& todoList);

#endif
