#ifndef USER_STRING
#define USER_STRING
#include <string>

std::string uppercase(std::string myString);
std::string getWordInSentence(std::string sentence, int wordNumber);
std::string getTextByCharLimits(std::string sentence, char lowerLimit, char upperLimit);
void loopTextByDifferentCharLimits(std::string& word, std::string sentence, char lowerLimit, char upperLimit);
void loopTextBySameCharLimits(std::string& word, std::string sentence, char delimiter);

#endif
