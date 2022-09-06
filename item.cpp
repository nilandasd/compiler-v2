// item.cpp

#include "item.hpp"


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

Item* Item::shiftCursor() {
  std::vector<int> b;
  Item *i = new Item(head, b, lookahead);

  bool flag = false;
  for (int k : body) {
    if (flag == false && k != CURSOR) {
      i->body.push_back(k);
    } else if (k == CURSOR) {
      flag = true;
    } else {
      flag = false;
      i->body.push_back(k);
      i->body.push_back(CURSOR);
    }
  }

  if (flag) throw std::runtime_error("attempted to shift cursor at end of item");
  
  return i;
}

std::vector<int> Item::postfix() {
  std::vector<int> result;

  int flag = -1;
  for (int i : body) {
    if (flag == 1) result.push_back(i);
    else if (flag == 0) flag = 1;
    else if (i == CURSOR) flag = 0;
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

bool Item::in(std::vector<Item*> items) {
  bool flag = false;
  for (auto k : items) {
    if (*this == *k) {
      flag = true;
      break;
    }
  }
  return flag;
}

std::vector<int> Item::production() {
  std::vector<int> result;

  for (int i : body) {
    if (i == CURSOR) continue;
    result.push_back(i);
  }

  return result;
}