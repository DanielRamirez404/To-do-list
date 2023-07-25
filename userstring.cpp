#include "userstring.h"
#include <string>
#include <cassert>

std::string uppercase(std::string myString) {
  for (size_t i = 0; i < myString.size(); i++)
    myString[i] = toupper(myString[i]);
  return myString;
}

std::string getWordInSentence(std::string sentence, int wordNumber) {
  std::string word{""};
  int wordCounter{1};
  for (size_t i = 0; i < sentence.size(); i++) {
    if(sentence[i] == ' ') {
      wordCounter++;
      if (wordCounter > wordNumber) break;    
    } else {
      if (wordCounter == wordNumber) word += sentence[i];
    }
  }
  return word;
}

std::string getTextByCharLimits(std::string sentence, char lowerLimit, char upperLimit) {
  std::string word{""};
  if (lowerLimit != upperLimit) {
    loopTextByDifferentCharLimits(word, sentence, lowerLimit, upperLimit);
  } else {
    loopTextBySameCharLimits(word, sentence, lowerLimit);
  }
  return word;
}

void loopTextByDifferentCharLimits(std::string& word, std::string sentence, char lowerLimit, char upperLimit) {
  bool isCharBetweenLimits{false};
  for (size_t i = 0; i < sentence.size(); i++) {
    if (sentence[i] == upperLimit) {
      isCharBetweenLimits = false;
      break;
    }
    if (isCharBetweenLimits) {
      word += sentence[i];
    }
    if (sentence[i] == lowerLimit) {
      isCharBetweenLimits = true;
    }
  }
  assert(!isCharBetweenLimits);
}

void loopTextBySameCharLimits(std::string& word, std::string sentence, char delimiter) {
  int characterOcurrences{0};
  for (size_t i = 0; i < sentence.size(); i++) {
    if (characterOcurrences == 2) {
      break;
    }
    if (characterOcurrences == 1) {
      word += sentence[i];
    }
    if (sentence[i] == delimiter) {
      characterOcurrences++;
    }
  }
  assert(characterOcurrences == 2);
}
