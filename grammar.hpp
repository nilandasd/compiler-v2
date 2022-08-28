// grammar.hpp

#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "token.hpp"

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

    Grammar(std::stringstream* s): ss{s} {};

    void read();
    void augmentStart();
    int tokenSymbol(Token* t);
    std::vector<int> first(int v);

  private:
    void readNonterminal(std::string s);
    void readProductions(Nonterminal* nt);
    std::vector<int> parseProduction(std::string s);
    void validateProduction(std::string s);
    int serialize(std::string s);

    std::stringstream* ss;
    int symbolCounter = 0;
};
