// grammar.hpp

#include <vector>



class Nonterminal {
  public:
    Nonterminal();

    int head;
    vector<vector<int>> productions;
};

class Grammar {
  public:
    readGrammar();

    unordered_map<int, Nonterminal> nonterminals;
    unordered_map<string, int> symbols;

  private:


};
