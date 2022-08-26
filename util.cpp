//util.cpp

#include "util.hpp"
#include <string>
#include <vector>

std::string capitalize(std::string s) {
  std::string result;

  for (auto & c: s) result += (char)toupper(c);

  return result;
}

bool emptyline(std::string s) {
  for (auto & c: s) if ( !isspace(c) ) return false;  

  return true;
}

bool onlyalpha(std::string s) {
  for (auto & c: s) if ( !isalpha(c) ) return false;

  return true;
}

std::vector<std::string> getwords(std::string s) {
  std::vector<std::string> result;

  for (auto & c : s) {
    std::string word;

    if (isspace(c)) {
      if ( word.length() != 0) result.push_back(word);
      word.clear();
      continue;
    }

    word += c;
  }

  return result;
}
