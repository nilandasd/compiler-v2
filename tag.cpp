//tag.cpp

#include "tag.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<int, string> specialTags ({
  {EQ,  "==" },
  {NEQ, "!=" },
  {GT,  ">"  },
  {GTE, ">=" },
  {LT,  "<"  },
  {LTE, "<=" },
  {END, "$"  }
});


string Tag::toString() {
  if ( id < 0 ) {
    return specialTags[id];    
  } else {
    return string(1, static_cast<char>(id));
  }
}

string IdTag::toString() {
  if ( reservedWord ) {
    return attr;
  } else {
    return "ID";
  }
}

string NumTag::toString() {
  return "NUM";
}
