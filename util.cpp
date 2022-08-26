//util.cpp

#include "util.hpp"
#include <string>
#include <vector>
#include <iostream>


std::string capitalize(std::string s) {
  std::string result;

  for (auto & c: s) result += (char)toupper(c);

  return result;
}

bool empty(std::string s) {
  for (auto & c: s) if ( !isspace(c) ) return false;  

  return true;
}

bool alpha(std::string s) {
  for (auto & c: s) if ( !isalpha(c) ) return false;

  return true;
}

std::vector<std::string> getwords(std::string s) {
  std::vector<std::string> result;
  
  std::string word;
  for (auto & c : s) {
    if (isspace(c)) {
      if ( word.length() != 0) 
        result.push_back(word);     

      word.clear();
      continue;
    }

    word += c;
  }

  if ( word.length() != 0 )
    result.push_back(word);

  return result;
}
