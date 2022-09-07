// state_test.cpp

#include "../state.hpp"
#include "../item.hpp"
#include <vector>
#include <cassert>
#include <iostream>


void kernel_test() {
  State s1(1);

  std::vector<int> v1{CURSOR, 1, 2, 3};
  std::vector<int> v2{1, CURSOR, 2, 3};
  std::vector<int> v3{1, 2, CURSOR, 3};
  std::vector<int> v4{1, 2, 3, CURSOR};

  Item *i1 = new Item(0, v1, DNE);
  Item *i2 = new Item(0, v2, DNE);
  Item *i3 = new Item(0, v3, DNE);
  Item *i4 = new Item(0, v4, DNE);

  s1.items.push_back(i1);
  s1.items.push_back(i2);
  s1.items.push_back(i3);
  s1.items.push_back(i4);

  assert(s1.kernel().size() == 3);
}

void compare_test() {
  State s1(1);
  State s2(2);
  State s3(3);

  std::vector<int> v1{1, CURSOR, 2, 3};
  std::vector<int> v2{1, 2, CURSOR, 3};
  std::vector<int> v3{1, 2, 3, CURSOR};

  Item *i1 = new Item(0, v1, DNE);
  Item *i2 = new Item(0, v2, DNE);

  Item *i3 = new Item(0, v1, DNE);
  Item *i4 = new Item(0, v2, DNE);

  Item *i5 = new Item(0, v1, DNE);
  Item *i6 = new Item(0, v3, DNE);
 
  s1.items.push_back(i1);
  s1.items.push_back(i2);
  s2.items.push_back(i3);
  s2.items.push_back(i4);
  s3.items.push_back(i5);
  s3.items.push_back(i6);

  assert(s1 == s2);
  assert(s1 != s3);
  assert(s2 != s3);
}

int main() {
  kernel_test();
  compare_test();
}

