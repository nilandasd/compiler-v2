// grammar.hpp

#pragma once

#include "token.hpp"
#include "item.hpp"
#include <sstream>
#include <set>

class Nonterminal {
  public:
    int head;
    std::vector<std::vector<int>> productions;

    Nonterminal(int x): head(x) {};
};

class Grammar {
  public:
    std::unordered_map<std::string, int> symbols;
    std::unordered_map<int, Nonterminal*> nonterminals;

    Grammar(std::stringstream* s): ss{s} {
      symbols["."] = CURSOR; 
    };

    void read();
    void augmentStart();
    int tokenSymbol(Token* t);
    std::vector<int> first(int v);
    std::vector<Item*> productionItems(int i);
    std::string symbolToString(int i);
    int serialize(std::string s);

  private:
    void readNonterminal(std::string s);
    void readProductions(Nonterminal* nt);
    std::vector<int> parseProduction(std::string s);
    void validateProduction(std::string s);

    std::stringstream* ss;
    int symbolCounter = 0;
};
