//util.cpp

#include <string>


std::string capitalizeString(std::string s) {
  std::string result;

  for (auto & c: s) result += (char)toupper(c);

  return result;
}

bool emptyLine(std::string s) {
  for (auto & c: s) if ( !isspace(c) ) return false;  

  return true;
}
