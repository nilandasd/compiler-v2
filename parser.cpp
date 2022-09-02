// parser.cpp

#include "parser.hpp"

using vec_size = std::vector<Item *>::size_type;

void Parser::init() {
  states.push_back(this->initialState());

  bool additions = true;
  while (additions) {
    additions = false;
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
        additions = true;
      }
    }
  }
}

State* SLR::initialState() {
  State *s = new State(0);
  std::vector<int> v{CURSOR, 1};
  Item *i = new Item(AUGMENTED_START, v, DNE);
  s->items.push_back(i);
  return s;
}

State* LALR::initialState() {
  State *s = new State(0);
  std::vector<int> v{CURSOR, 1};
  Item *i = new Item(AUGMENTED_START, v, ACCEPT);
  s->items.push_back(i);
  return s;
}


void Parser::print() {
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

bool Parser::stateAlreadyExists(State *newState) {
  for (auto state : states) {
    if (*state == *newState) return true;
  }
  return false;
}

State* Parser::move(std::vector<Item*> items, int e) {
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
      if (newItem->in(result)) {
       delete newItem;
       continue;
      }
      result.push_back(newItem);
      if (G.nonterminals.find(e) != G.nonterminals.end()) {
        std::vector<Item*> newItems = G.productionItems(e);
        for (auto newItem : newItems) {
          if (newItem->in(result)) {
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

std::vector<Item*> LALR::closure(State *state) {
  std::vector<Item*> result;

  for (auto item : state->items) {
    result.push_back(item);
  }

  bool addition = true;
  while (addition) {
    addition = false;

    for (vec_size k = 0; k < result.size(); ++k) {
      Item* item = result[k];
      int e = item->expects();
      std::vector<int> postfix = item->postfix();
      if (e == DNE) continue;
      if (postfix.size() == 0) postfix.push_back(item->lookahead);
      std::vector<Item*> prods = G.productionItems(e);
      if (prods.size() == 0) continue;
      for (Item* prodItem : prods) {
        for (int lookahead : G.first(postfix[0])) {
          Item* newItem = new Item(prodItem->head, prodItem->body, lookahead);
          if (item->in(result)) {
            delete newItem;
            continue;
          }
        result.push_back(newItem);
        addition = true;
      }
      }
    }
  }
  return result;
}