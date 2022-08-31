// slr_test.cpp

#include <cassert>
#include "../grammar.hpp"
#include "../slr.hpp"
#include <sstream>
#include <iostream>
#include <fstream>

void test_init1() {
  std::stringstream ss;
  ss << "START\n\t| w1 w2 w3";
  Grammar G(&ss);  
  G.read();
  G.augmentStart();

  SLR slr(G);
  slr.init();

  assert(slr.states.size() == 5);
  assert(slr.states[0]->items.size() == 1);
  assert(slr.states[0]->items[0]->head == AUGMENTED_START);
  assert(slr.states[0]->items[0]->body.size() == 2);
  assert(slr.states[0]->items[0]->body[0] == CURSOR);
  assert(slr.states[0]->items[0]->body[1] == 1);
}

void test_init2() {
  std::stringstream ss;
  ss << "START\n\t| NT w2 w3\n\nNT\n\t| w4";
  Grammar G(&ss);  
  G.read();
  G.augmentStart();

  SLR slr(G);
  slr.init();

  assert(slr.states.size() == 6);
  assert(slr.states[0]->items.size() == 1);
  assert(slr.states[0]->items[0]->head == AUGMENTED_START);
  assert(slr.states[1]->items[0]->body.size() == 2);
  assert(slr.states[1]->items[0]->body[0] == 1);
  assert(slr.states[1]->items[0]->body[1] == CURSOR);

  for (auto state : slr.states) {
    for (auto item : state->items) {
      assert(item->lookahead == DNE);
    }
  }
}

void test_init3() {
  std::stringstream ss;
  ss << "START\n\t| NT w2 w3\n\nNT\n\t| w4";
  Grammar G(&ss);  
  G.read();
  G.augmentStart();

  SLR slr(G);
  slr.init();

}

int main() {
  test_init1();
  test_init2();
  test_init3();
}