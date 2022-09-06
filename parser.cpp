// parser.cpp

#include "parser.hpp"

// BASE CLASS PARSER

void Parser::print() {
  for (auto p : states) {
    State *state = p.second;
    std::cout << state->id << std::endl;
    std::cout << "\tMOVES: ";
    for (auto p : state->moves) {
      std::cout << "<'" << G.symbolToString(p.first) << "', " << p.second->id << ">,  ";
    }
    std::cout << std::endl;
    for (auto item : state->items) {
      std::cout << "\t|  " << G.symbolToString(item->head) << "  =>  ";
      for (auto i : item->body) {
        std::cout << " " << G.symbolToString(i);
      }
      std::cout << "\tLA: " << G.symbolToString(item->lookahead) << std::endl;
    }
    std::cout << std::endl;
  }
}

State* Parser::stateAlreadyExists(State *newState) {
  for (auto p : states) {
    State *state = p.second;
    if (*state == *newState) {
      return state;
    }
  }
  return NULL;
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

// CLASS SLR (SIMPLE LR PARSER)
// L => read text left to right
// R => always expand the rightmost nonterminal on the stack
// only used for efficient construction of the LALR, not actually used in parsing

void SLR::init() {
  states[0] = this->initialState();

  bool additions = true;
  while (additions) {
    additions = false;
    for (vec_size i = 0; i < states.size(); ++i) {
      State *state = states[i];
      std::unordered_map<int, bool> moved;
      std::vector<Item*> items = closure(state->items);
      for (auto item : items) {
        int e = item->expects();
        if (e == DNE || moved[e]) continue;
        State *newState = move(items, e);
        moved[e] = true;

        State *existingState = stateAlreadyExists(newState);
        if (existingState) {
          state->moves[e] = existingState;
          delete newState;
          continue;
        }

        state->moves[e] = newState;
        states[newState->id] = newState;
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

std::vector<Item *> SLR::closure(std::vector<Item*> items) {
  std::vector<Item *> result;

  for (auto item : items) {
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

      if (G.nonterminalExists(e)) {
        std::vector<Item*> newItems = G.productionItems(e);
        for (auto newItem : newItems) {
          if (newItem->in(result)) {
            delete newItem;
            continue;
          }
          addition = true;
          result.push_back(newItem);
        }
      }
    }
  }
  return result;
}

// CLASS LALR
// LA => Look Ahead ()
// this is the parser that is actually used to parse the grammar

void LALR::init() {
  SLR slr(G);
  slr.init();
  copySLR(slr);

  propagateLookaheads(slr.states);

  createParsingTable();
}

std::vector<Item*> LALR::closure(std::vector<Item*> items) {
  std::vector<Item*> result;

  for (auto item : items) {
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
      postfix.push_back(item->lookahead);
      std::vector<Item*> prods = G.productionItems(e);
      if (prods.size() == 0) continue;
      for (Item* prodItem : prods) {
        for (int lookahead : G.first(postfix[0])) {
          Item* newItem = new Item(prodItem->head, prodItem->body, lookahead);
          if (newItem->in(result)) {
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

void LALR::initPropagationTable (std::unordered_map<int, State*> kernel) {
  std::vector<int> v{CURSOR, 1};
  Item *i = new Item(AUGMENTED_START, v, ACCEPT);
  addLookahead(0, i, i->lookahead);

  for (auto p : kernel) {
    State* state = p.second;
    for (Item* item : state->items) {
      std::vector<Item*> v {item};
      std::vector<Item*> J = closure(v);

      for (Item* i : J) {
        int e = i->expects();
        if (e == DNE) continue;

        Item *newItem = i->shiftCursor();
        if (i->lookahead != DNE) {
          addLookahead(state->moves[e]->id, newItem, i->lookahead);
        } else {
          addPropagation({state->id, item}, {state->moves[e]->id, newItem});
        }
      }
    }
  }
}

void LALR::propagateLookaheads(std::unordered_map<int, State*> kernel) {
  initPropagationTable(kernel);

  bool addition = true;
  while(addition) {
    addition = false;
    for (propagator p : propagationTable) {
      for (itemId target : *p.second) {
        for (int la : findLookAheads(p.first)) {
          if (addLookahead(target.first, target.second, la)) addition = true;
        }
      }
    }
  }
}

void LALR::addPropagation(itemId source, itemId target) {
  for (auto p : propagationTable) {
    itemId iid = p.first;
    if (iid.first == source.first && *(iid.second) == *(source.second)) {
      p.second->push_back(target);
      return;
    }
  }
  propagationTable.push_back({source, new std::vector<itemId> {target}});
}

bool LALR::addLookahead(int sid, Item *i, int la) {
  Item *newItem = new Item(i->head, i->body, la);

  for ( auto item : states[sid]->items) {
    if (*item == *newItem) {
      delete newItem;
      return false;
    }
  }

  states[sid]->items.push_back(newItem);
  return true;
}

std::vector<int> LALR::findLookAheads(itemId source) {

  std::vector<int> result;
  for ( auto item : states[source.first]->items) {
    source.second->lookahead = item->lookahead;
    
    if (*item == *source.second) {
      result.push_back(item->lookahead);
    }
  }
  return result;
}

void LALR::copySLR(SLR &slr) {
  for (auto p : slr.states) {
    State* state = p.second;
    State* newState = new State(state->id);
    for (auto move : state->moves) {
      newState->moves[move.first] = move.second;
    }
    states[newState->id] = newState;
  }
}

void LALR::createParsingTable() {
  for (auto p : states) {
    State* state = p.second;
    std::unordered_map<int, Item*> reduceReduceConflicts;

    for (auto move : state->moves) {
      if (G.nonterminalExists(move.first)) {
        moveTable[state->id][move.first] = move.second->id;
      }
    }

    for (Item* item : closure(state->items)) {
      int e = item->expects();
      if (e != DNE && (!G.nonterminalExists(e)) && (state->moves.find(e) != state->moves.end())) {
        actionTable[state->id][e] = { SHIFT, state->moves[e]->id };
        continue;
      } else if (e == DNE && item->head != AUGMENTED_START){
        int la = item->lookahead;
        if (actionTable[state->id].find(la) != actionTable[state->id].end()) {
          if (actionTable[state->id][la].first == SHIFT) // RESOLVES SHIFT / REDUCE CONFLICTS
            continue;

          if (!G.productionPrecedes(item, reduceReduceConflicts[e])) // RESOLVES REDUCE / REDUCE CONFLICTS
            continue;

          reduceReduceConflicts[la] = item;
        }
        actionTable[state->id][la] = { REDUCE, G.productionNumber(item) };
      } else if (e == DNE && item->head == AUGMENTED_START){
        actionTable[state->id][ACCEPT] = { ACCEPT, DNE };
      }
    }
  }
}

void LALR::printActionTable() {
  for (auto at : actionTable) {
    std::cout << "STATE " << at.first << ":"<< std::endl;
    for (auto action : at.second) {
      std::cout << "\t'" << G.symbolToString(action.first) << "' ";
      if (action.second.first == SHIFT) {
        std::cout << "SHIFT: " << action.second.second;
      } else if (action.second.first == REDUCE) {
        std::cout << "REDUCE: " << action.second.second;
      } else {
        std::cout << "ACCEPT!!!";
      }
      std::cout << std::endl;
    }
    std::cout << "\tGOTO: ";
    for (auto move : moveTable[at.first]) {
      std::cout << " <'" << G.symbolToString(move.first) << "',  " << move.second << ">";
    }
    std::cout << std::endl;
  }
}

void LALR::parse(std::vector <int> input) {
  int k = 0;
  int a = input[k]; // token
  stack.push_back(0);
  while(true) {
    int s = stack.back();
    std::cout << "STACK: ";
    for(auto i : stack) {
      std::cout << i << ", ";
    }
    std::cout << "ACTION: " << G.symbolToString(a) << std::endl;
    if (actionTable[s].find(a) == actionTable[s].end()) throw std::runtime_error("parsing error"); 
    action act = actionTable[s][a];

    if (act.first == REDUCE) {
      

      std::pair<int, std::vector<int>> production = G.getProduction(act.second);
      std::cout << "reducing: " << G.symbolToString(production.first) << " => ";
      for (auto g : production.second) {
        std::cout << G.symbolToString(g) << ", ";
      }
      std::cout << std::endl;
      for (int i = 0; i < production.second.size(); i++) {
        stack.pop_back();
      }
      std::cout << "Goto: " << moveTable[stack.back()][production.first] << std::endl;
      stack.push_back(moveTable[stack.back()][production.first]);
    } else if (act.first == SHIFT) {
      std::cout << "shifting " << act.second << std::endl;
        stack.push_back(act.second);
        k++;
        a = input[k];
    } else {
      break;
    }
  }
  std::cout << "grammar acepted!" << std::endl;
}
