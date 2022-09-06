// parser.hpp

#pragma once

#include "grammar.hpp"
#include "state.hpp"

using vec_size = std::vector<Item *>::size_type;
using itemId = std::pair<int, Item*>;
using propagator = std::pair<itemId, std::vector<itemId>*>;
using action = std::pair<int, int>;

class Parser {
  public:
    Parser(Grammar &g): G{g} {};
    virtual void init() = 0;
    void print();
    std::unordered_map<int, State*> states;

  protected:
    virtual std::vector<Item*> closure(std::vector<Item*> items) = 0;
    State* move(std::vector<Item*> items, int i);
    State* stateAlreadyExists(State *state);
    Grammar &G;
};
class SLR: public Parser {
  public:
    SLR(Grammar &g): Parser(g) {};
    virtual void init();

  private:
    virtual std::vector<Item*> closure(std::vector<Item*> items);
    State* initialState();
};

class LALR: public Parser  {
  public:
    LALR(Grammar &g): Parser(g) {};
    virtual void init();
    void printActionTable();
    void parse(std::vector <int> input);
    std::unordered_map<int, std::unordered_map<int, action>> actionTable;
    std::unordered_map<int, std::unordered_map<int, int>> moveTable;

  private:
    virtual std::vector<Item*> closure(std::vector<Item*> items);
    std::vector<int> findLookAheads(itemId source);
    bool addLookahead(int sid, Item *i, int la);
    void addPropagation(itemId source, itemId target);
    void initPropagationTable (std::unordered_map<int, State*> kernel);
    void propagateLookaheads(std::unordered_map<int, State*> kernel);
    void copySLR(SLR &slr);
    void createParsingTable();

    std::vector<propagator> propagationTable;
    std::vector<int> stack;
};