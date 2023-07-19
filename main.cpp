#include "main.h"
#include "linked list.h"
#include <iostream>
#include <string>
#include <string_view>

int main() {
  linkedList<std::string_view> todoList;
  todoList.append("Watch Oshi no Ko");
  todoList.append("Reread One Piece");
  todoList.preppend("Study kanji");
  todoList.preppend("(Keep) Play(ing) Stardew Valley");
  todoList.preppend("Finish to-do list");
  todoList.append("Make another website");
  todoList.append("Work on secret project");
  while (todoList.iterate() !=  NULL) {
    std::cout << "* " << todoList.getIteratorValue() << '\n';
  }
  return 0;
}
