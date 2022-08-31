// test_item.cpp

#include "../item.hpp"
#include <cassert>
#include <vector>
#include <stdexcept>
#include <string>

void test_comparison() {
  std::vector<int> v1{CURSOR, 1, 2, 3, 4, 5};
  std::vector<int> v2{1, CURSOR, 2, 3, 4, 5};

  Item i1(0, v1, DNE);
  Item i2(0, v1, DNE);
  Item i3(1, v1, DNE);
  Item i4(0, v2, DNE);
  Item i5(0, v2, 0);

  assert(i1 == i2);
  assert(i1 != i3);
  assert(i1 != i4);
  assert(i4 != i5);
}

void test_expects() {
  std::vector<int> v1{CURSOR, 1, 2, 3, 4, 5};
  std::vector<int> v2{CURSOR};
  Item i1(0, v1, DNE);
  Item i2(0, v2, DNE);

  assert(i1.expects() == 1);
  assert(i2.expects() == DNE);
}

void test_postfix() {
  std::vector<int> v1{CURSOR, 1, 2, 3, 4, 5};
  std::vector<int> v2{1, 2, CURSOR, 3};
  std::vector<int> v3{1, 2, 3, CURSOR};

  Item i1(0, v1, DNE);
  Item i2(0, v2, DNE);
  Item i3(0, v3, DNE);

  std::vector<int> r = i1.postfix();
  assert(r.size() == 5);
  assert(r[0] == 1);
  assert(r[4] == 5);

  r = i2.postfix();
  assert(r.size() == 1);
  assert(r[0] == 3);
  
  r = i3.postfix();
  assert(r.size() == 0);
}

void test_shiftCursor() {
  std::vector<int> v1{CURSOR, 1, 2, 3};
  std::vector<int> v2{1, CURSOR, 2, 3};
  std::vector<int> v3{1, 2, CURSOR, 3};
  std::vector<int> v4{1, 2, 3, CURSOR};
  
  Item i1(0, v1, DNE);
  Item i2(0, v2, DNE);
  Item i3(0, v3, DNE);
  Item i4(0, v4, DNE);
  

  Item *r = i1.shiftCursor();
  assert(r->body[1] == CURSOR);
  assert(*r == i2);
  r = r->shiftCursor();
  assert(r->body[2] == CURSOR);
  assert(*r == i3);
  r = r->shiftCursor();
  assert(r->body[3] == CURSOR);
  assert(*r == i4);

  try {
    r = r->shiftCursor();
    assert(false);
  } catch(std::runtime_error &e) {
    std::string s(e.what());
    assert(s.compare("attempted to shift cursor at end of item") == 0);
  }
}

int main() {
  test_comparison();
  test_expects();
  test_postfix();
  test_shiftCursor();
}
