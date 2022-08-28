// util_test.cpp

#include "../util.hpp"
#include <cassert>
#include <vector>
#include <string>

void test_empty() {
  assert(empty("	") == true);
  assert(empty("") == true);
  assert(empty("    test   ") == false);
  assert(empty("\t\n\t   "));
}

void test_alpha() {
  assert(alpha("asdfasd"));
  assert(!alpha("asdf876"));
  assert(!alpha("    test   "));
  assert(!alpha("9870870"));
}

void test_getwords() {
  std::string s1("TEST1 TEST2 TEST3");

  std::vector<std::string> v = getwords(s1);

  assert(v.size() == 3);
  assert(v[0].compare("TEST1") == 0);
  assert(v[1].compare("TEST2") == 0);
  assert(v[2].compare("TEST3") == 0);

  std::string s2("\t| w1 w2 w3");

  v = getwords(" w1 w2 w3");

  assert(v.size() == 3);
  assert(v[0].compare("w1") == 0);
  assert(v[1].compare("w2") == 0);
  assert(v[2].compare("w3") == 0);
}


int main() {
  test_empty();
  test_alpha();
  test_getwords();
}
