//util.cpp

#include <string>


std::string capitalizeString(std::string s) {
  std::string result;

  for (auto & c: s) result += (char)toupper(c);

  return result;
}
