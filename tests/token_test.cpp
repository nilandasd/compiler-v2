// token_test.cpp

#include "../token.hpp"
#include <cassert>
#include <iostream>

void test_Token() {
  Token t(42);

  assert(t.id == 42);
  assert(t.toString() == "*");
}

void test_IdToken() {
  IdToken t1("test");

  assert(t1.id == ID);
  assert(t1.toString().compare("ID") == 0);
  assert(t1.attr.compare("test") == 0);
  assert(t1.reservedWord == false);

  IdToken t2("if");

  assert(t2.id == IF);
  assert(t2.toString().compare("IF") == 0);
  assert(t2.attr.compare("if") == 0);
  assert(t2.reservedWord == true);
}

void test_NumToken() {
  NumToken t1(42);

  assert(t1.id == NUM);
  assert(t1.toString().compare("NUM") == 0);
  assert(t1.attr == 42);
}

int main() {
 
  test_Token();

  test_IdToken();

  test_NumToken();
}
