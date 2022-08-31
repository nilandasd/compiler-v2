// slr.cpp

#include "slr.hpp"
#include "state.hpp"
#include <vector>
#include <unordered_map>
#include <iostream>

using vec_size = std::vector<Item *>::size_type;

void SLR::init() {
  states.push_back(initialState());

  int additions = -1;
  while (additions != 0) {
    additions = 0;
    for (vec_size i = 0; i < states.size(); ++i) {
      State *state = states[i];
      std::unordered_map<int, bool> moved;
      std::vector<Item*> items = closure(state);
      for (auto item : items) {
        int e = item->expects();
        if (e == DNE || moved[e]) continue;
        moved[e] = true;
        State *newState = move(items, e);
        if (stateAlreadyExists(newState)) {
          delete newState;
          continue;
        }
        states.push_back(newState);
        additions += 1;
      }
    }
  }
}

State *SLR::move(std::vector<Item*> items, int e) {
  State *result = new State(states.size());

  for (auto item : items) {
    if (item->expects() == e) {
      result->items.push_back(item->shiftCursor());
    }
  }

  return result;
}

std::vector<Item *> SLR::closure(State *state) {
  std::vector<Item *> result;

  for (auto item : state->items) {
    result.push_back(item);
  }

  bool addition = true;
  while (addition) {
    addition = false;

    for (vec_size i = 0; i < result.size(); ++i) {
      Item *item = result[i];
      int e = item->expects();
      if (e == DNE)
        continue;
      Item *newItem = item->shiftCursor();

      if (itemAlreadyExists(result, newItem)) {
       delete newItem;
       continue;
      }

      result.push_back(newItem);
      if (G.nonterminals.find(e) != G.nonterminals.end()) {
        std::vector<Item*> newItems = G.productionItems(e);

        for (auto newItem : newItems) {
          if (itemAlreadyExists(result, newItem)) {
            delete newItem;
            continue;
          }
          result.push_back(newItem);
        }
      }
      addition = true;
    }
  }
  return result;
}

bool SLR::itemAlreadyExists(std::vector<Item*> items, Item* item) {
  bool flag = false;
  for (auto k : items) {
    if (*item == *k) {
      flag = true;
      break;
    }
  }
  return flag;
}

bool SLR::stateAlreadyExists(State *newState) {
  for (auto state : states) {
    if (*state == *newState) return true;
  }
  return false;
}

State* SLR::initialState() {
  State *s = new State(0);
  std::vector<int> v{CURSOR, 1};
  Item *i = new Item(AUGMENTED_START, v, DNE);
  s->items.push_back(i);
  return s;
}

void SLR::print() {
   for (auto state : states) {
    std::cout << state->id << std::endl;
    for (auto item : state->items) {
      std::cout << "\t|  " << G.symbolToString(item->head) << "  =>  ";
      for (auto i : item->body) {
        std::cout << " " << G.symbolToString(i);
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}