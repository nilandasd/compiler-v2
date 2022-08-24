//util.cpp

#pragma once
#include <string>


string capitalizeString(string s) {
  string result;

  for (auto & c: s) result += (char)toupper(c);

  return result;
}
