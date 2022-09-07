// state.hpp

#pragma once

#include "grammar.hpp"

class State {
  public:
    State(int i): id(i) {};
    ~State() {
      for(auto item : items) {
        delete item;
      }
    };

    int id;
    std::vector<Item*> items;
    std::unordered_map<int, State*> moves;
    
    bool operator==(const State &other);
    bool operator!=(const State &other);

    std::vector<Item*> kernel() const; 
};


