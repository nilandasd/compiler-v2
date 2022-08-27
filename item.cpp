// item.cpp

#include "item.hpp"
#include <vector>
#include <stdexcept>

int Item::expects() {
  bool flag = false;
  for (int i : body) {
    if (i == CURSOR) {
      flag = true;
      continue;
    }
    if (flag) return i;
  }

  return DNE;
}

Item Item::shiftCursor() {
  std::vector<int> b;
  Item i(head, b, lookahead);

  bool flag = false;
  for (int k : body) {
    if (flag == false && k != CURSOR) {
      i.body.push_back(k);
    } else if (k == CURSOR) {
      flag = true;
    } else {
      flag = false;
      i.body.push_back(k);
      i.body.push_back(CURSOR);
    }
  }

  if (flag) throw std::runtime_error("attempted to shift cursor at end of item");
  
  return i;
}

std::vector<int> Item::postfix() {
  std::vector<int> result;

  bool flag = false;
  for (int i : body) {
    if (flag) result.push_back(i);
    if (i == CURSOR) flag = true;
  }

  return result;
}

bool Item::operator==(const Item& other) {
  if (other.lookahead != this->lookahead ||
      other.head != this->head ||
      other.body.size() != this->body.size())
    return false;

  for(std::vector<int>::size_type k = 0; k < this->body.size(); k++) {
    if (this->body[k] != other.body[k]) return false;
  }

  return true;
}

bool Item::operator!=(const Item& other) {
  return !(*this == other);
}
