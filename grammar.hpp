// grammar.hpp

#pragma once

#include <vector>
#include <unordered_map>

class Nonterminal {
  public:
    int head;
    vector<vector<int>> productions;

    Nonterminal();

};

class Grammar {
  public:
    unordered_map<string, int> symbols;
    unordered_map<int, Nonterminal> nonterminals;

    Grammar();
    readGrammar();

};
