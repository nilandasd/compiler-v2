// state.cpp

#include "state.hpp"
#include "item.hpp"
#include "grammar.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>

using vec_size = std::vector<Item*>::size_type;

bool State::operator==(const State &other) {
  std::vector<Item*> v1 = this->kernel();
  std::vector<Item*> v2 = other.kernel();

  if (v1.size() != v2.size()) return false;

  // by definition each item in a kernel is unique
  std::unordered_map<int, bool> matched;
  for (vec_size i = 0; i < v1.size(); ++i) {
    bool flag = true;
    if ( matched[i] ) continue;
    for (vec_size k = 0; k < v1.size(); ++k) {
      if ( (*v1[i]) == (*v2[k])) {
        matched[i] = true;
        flag = false;
        break;
      }
    }
    if (flag) return false;
  }

  return true;
}

bool State::operator!=(const State &other) {
  return !(*this == other);
}

std::vector<Item*> State::kernel() const {
  std::vector<Item*> k;

  for (auto i : items) {
    if(i->body[0] != CURSOR || i->head == AUGMENTED_START)
      k.push_back(i);
  }

  return k;
}
