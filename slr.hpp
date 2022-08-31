// slr.hpp

#include "grammar.hpp"
#include "state.hpp"
#include <vector>

/* 
  SLR Parser: "simpler LR" parser
  
  L stands for reads input 'L'eft to right.
  R stands for always deriving(ie expanding) the 'R'ight most nonterminal.

  This SLR is used only for getting the canonical kernel items
  for efficient construction of the LALR automaton. This SLR
  is not used for constructing a completed parse table. The 
  actual parse table is constructed by the LALR in lalr.cpp.
*/
class SLR {
  public:
    std::vector<State*> states;
    SLR(Grammar &g): G{g} {};
    void init();
    void print();

  private:
    State* initialState();
    State* move(std::vector<Item*> items, int i);
    std::vector<Item*> closure(State* s);
    bool stateAlreadyExists(State *s);
    bool itemAlreadyExists(std::vector<Item*> items, Item* item);
    Grammar &G;
};
