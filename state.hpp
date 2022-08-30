// state.hpp

#pragma once

#include "item.hpp"
#include <vector>
#include <unordered_map>


class State {
  public:
    State(int i): id(i) {};

    int id;
    std::vector<Item*> items;
    std::unordered_map<int, State*> moves;
    
    bool operator==(const State &other);
    bool operator!=(const State &other);

    std::vector<Item*> kernel() const; 
};


