#include "to-do list fstream.h"
#include "userstring.h"
#include "linked list.h"
#include <fstream>
#include <string>


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

void readSavedData(linkedList<std::string>& todoList) {
  std::fstream textFile{"todolist.txt", std::ios::in};
  std::string textLine{};
  for (size_t i{0}; std::getline(textFile, textLine); ++i) {
    if (textLine[0] == '*') {
      todoList.append(getTextByCharLimits(textLine, '[', ']'));
    }
  }
  textFile.close();
}

void saveTodoListData(linkedList<std::string>& todoList) {
  remove("todolist.txt");
  std::fstream textFile{"todolist.txt", std::ios::out};
  if (todoList.isEmpty()) {
    textFile << "[NO DATA AVAILABLE]";
  } else {
    textFile << "[DATA AVAILABLE]";
    textFile << "\n<<< ---------------------------------------- >>>";
    while (todoList.iterate() != nullptr) {
      textFile << "\n* [" << (todoList.getIteratorValue()) << ']';
    }
    textFile << "\n<<< ---------------------------------------- >>>";
  }
  textFile.close();
}
