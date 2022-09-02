// parser.hpp

#pragma once

#include "grammar.hpp"
#include "state.hpp"

class Parser {
  public:
    std::vector<State*> states;
    Parser(Grammar &g): G{g} {};
    void init();
    void print();

  protected:
    virtual std::vector<Item*> closure(State* state) = 0;
    virtual State* initialState() = 0;
    State* move(std::vector<Item*> items, int i);
    bool stateAlreadyExists(State *state);
    Grammar &G;
};

class LALR: public Parser  {
  public:
    LALR(Grammar &g): Parser(g) {};
  private:
    virtual std::vector<Item*> closure(State *state);
    virtual State* initialState();
};

class SLR: public Parser {
  public:
    SLR(Grammar &g): Parser(g) {};
  private:
    virtual std::vector<Item*> closure(State* state);
    virtual State* initialState();
};
