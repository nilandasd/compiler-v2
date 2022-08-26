

#include "../grammar.hpp"
#include "../lexer.hpp"
#include <iostream>
#include <cassert>

void test_one() {
  std::stringstream ss;
  Grammar G(&ss);

  ss << "START\n\t| w1 w2 w3";
  
  G.read();

  assert(G.symbols.size() == 4);
  assert(G.nonterminals.size() == 1);
  assert(G.symbols["START"] == 1);
  assert(G.symbols["w1"] == 2);
  assert(G.symbols["w2"] == 3);
  assert(G.symbols["w3"] == 4);

  Nonterminal* nt = G.nonterminals[G.symbols["START"]];

  assert(nt->head == G.symbols["START"]);
  assert(nt->productions.size() == 1);
  assert(nt->productions[0].size() == 3);
  assert(nt->productions[0][0] == G.symbols["w1"]);
  assert(nt->productions[0][1] == G.symbols["w2"]);
  assert(nt->productions[0][2] == G.symbols["w3"]);
}

void test_two() {
  std::stringstream ss;
  Grammar G(&ss);
  
  ss << "START\n\t| w1 w2 w3\n\t| w4 w5";
  
  G.read();
  
  assert(G.symbols.size() == 6);
  assert(G.nonterminals.size() == 1);
  assert(G.symbols["START"] == 1);
  assert(G.symbols["w1"] == 2);
  assert(G.symbols["w2"] == 3);
  assert(G.symbols["w3"] == 4);
  assert(G.symbols["w4"] == 5);
  assert(G.symbols["w5"] == 6);
  
  Nonterminal* nt = G.nonterminals[G.symbols["START"]];
  
  assert(nt->head == G.symbols["START"]);
  assert(nt->productions.size() == 2);
  assert(nt->productions[0].size() == 3);
  assert(nt->productions[0][0] == G.symbols["w1"]);
  assert(nt->productions[0][1] == G.symbols["w2"]);
  assert(nt->productions[0][2] == G.symbols["w3"]);
  
  assert(nt->productions[1].size() == 2);
  assert(nt->productions[1][0] == G.symbols["w4"]);
  assert(nt->productions[1][1] == G.symbols["w5"]);
}

void test_three() {
  std::stringstream ss;
  Grammar G(&ss);

  ss << "START\n\t| w1\n\nNT\n\t| w2";

  G.read();

  assert(G.symbols.size() == 4);
  assert(G.nonterminals.size() == 2);
  assert(G.symbols["START"] == 1);
  assert(G.symbols["w1"] == 2);
  assert(G.symbols["NT"] == 3);
  assert(G.symbols["w2"] == 4);

  Nonterminal* nt = G.nonterminals[G.symbols["START"]];

  assert(nt->head == G.symbols["START"]);
  assert(nt->productions.size() == 1);
  assert(nt->productions[0].size() == 1);
  assert(nt->productions[0][0] == G.symbols["w1"]);
  
  delete nt;
  nt = G.nonterminals[G.symbols["NT"]];

  assert(nt->head == G.symbols["NT"]);
  assert(nt->productions.size() == 1);
  assert(nt->productions[0].size() == 1);
  assert(nt->productions[0][0] == G.symbols["w2"]);
}

int main() {
  test_one();
  test_two();
  test_three();
}
