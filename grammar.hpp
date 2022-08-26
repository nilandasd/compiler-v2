// grammar.hpp

#pragma once

#include <vector>
#include <unordered_map>

class Nonterminal {
  public:
    int head;
    vector<vector<int>> productions;

    Nonterminal(int x): head(x) {};
};

class Grammar {
  public:
    unordered_map<string, int> symbols;
    unordered_map<int, Nonterminal> nonterminals;

    Grammar(std::stringstream* s): ss{s} {};
    void read();
    int tokenToSymbol(Token* t);

  private:
    void readNonterminal(string s);
    void readProductions(Nonterminal* nt);
    vector<int> parseProduction(string s);
    void validateProduction(string s);
    int serialize(string s);

    std::stringstream* ss;
    int symbolCounter = 256;
};
