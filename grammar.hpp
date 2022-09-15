// grammar.hpp

#pragma once

#include "token.hpp"
#include "item.hpp"
#include <sstream>
#include <set>

using productionId = std::pair<int, int>;

class Nonterminal {
  public:
    int head;
    std::vector<std::vector<int>> productions;
    Nonterminal(int x): head(x) {};
};

class Grammar {
  public:
    std::unordered_map<std::string, int> symbols;
    std::vector<Nonterminal*> nonterminals;
    Grammar(std::stringstream* s): ss{s} {
      symbols["."] = CURSOR;
      symbols["ACCEPT"] = ACCEPT; 
    };
    void read();
    void augmentStart();
    int tokenSymbol(Token* t);
    std::vector<int> first(int v);
    std::vector<Item*> productionItems(int i);
    std::string symbolToString(int i);
    int serialize(std::string s);
    bool productionPrecedes(Item* a, Item* b);
    int productionNumber(Item* item);
    bool nonterminalExists(int i);
    Nonterminal* getNonterminal(int i);
    std::pair<int, std::vector<int>> getProduction(int pid);

  private:
    void readNonterminal(std::string s);
    void readProductions(Nonterminal* nt);
    std::vector<int> parseProduction(std::string s);
    void validateProduction(std::string s);
    std::stringstream* ss;
    int symbolCounter = 0;
};
