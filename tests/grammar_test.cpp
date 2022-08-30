// grammar_test.cpp

#include "../grammar.hpp"
#include "../lexer.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>

void test_read1() {
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

void test_read2() {
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

void test_read3() {
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

void test_bad_nonterminal() {
  std::stringstream ss;
  Grammar G(&ss);

  ss << "START2903875\n\t| w1\n";

  try {
    G.read();
    assert(true == false);
  } catch(std::runtime_error &e) {
    std::string w(e.what());
    assert(w.compare("BAD GRAMMAR FILE: nonterminal can only be letters") == 0);
  }
}

void test_missing_productions() {
  std::stringstream ss;
  Grammar G(&ss);

  ss << "START\n\n\t| w1\n";

  try {
    G.read();
    assert(true == false);
  } catch(std::runtime_error &e) {
    std::string w(e.what());
    assert(w.compare("BAD GRAMMAR FILE: Nonterminal must have at least one production") == 0);
  }
}

void test_invalid_production() {
  std::stringstream ss;
  Grammar G(&ss);

  ss << "START\n\tbad w1\n";

  try {
    G.read();
    assert(true == false);
  } catch(std::runtime_error &e) {
    std::string w(e.what());
    assert(w.compare("BAD GRAMMAR FILE: invalid production") == 0);
  }
}

void test_first() {
  std::stringstream ss;
  Grammar G(&ss);

  ss << "START\n\t| w1 w2 w3";

  G.read();

  assert(G.first(1).size() == 1);
  assert(G.first(1)[0] == G.symbols["w1"]);

  std::stringstream ss2;
  ss2 << "START\n\t| AAA x x\n"
         "\t| BBB x\n"
         "\t| CCC\n"
         "\t| 6 DDD\n\n"
         "AAA\n"
	 "\t| 1 x\n"
         "\t| EEE\n\n"
	 "BBB\n"
 	 "\t| 3\n"
	 "\t| 4\n\n"
         "CCC\n"
	 "\t| BBB\n"
         "\t| CCC x\n"
         "\t| 5\n\n"
         "DDD\n"
	 "\t| x\n\n"
         "EEE\n"
	 "\t| 2\n\n"
	 "FFF\n"
	 "\t| x";

  Grammar G2(&ss2);
  G2.read();
  
  std::vector<int> f = G2.first(1);
  assert(f.size() == 6);
  assert(std::find(f.begin(), f.end(), G2.symbols["1"]) != f.end());
  assert(std::find(f.begin(), f.end(), G2.symbols["2"]) != f.end());
  assert(std::find(f.begin(), f.end(), G2.symbols["3"]) != f.end());
  assert(std::find(f.begin(), f.end(), G2.symbols["4"]) != f.end());
  assert(std::find(f.begin(), f.end(), G2.symbols["5"]) != f.end());
  assert(std::find(f.begin(), f.end(), G2.symbols["6"]) != f.end());
  assert(std::find(f.begin(), f.end(), G2.symbols["x"]) == f.end());
}

void test_augmentStart() {
 std::stringstream ss;
  Grammar G(&ss);

  ss << "START\n\t| w1\n\nNT\n\t| w2";

  G.read();
  G.augmentStart();

  assert(G.symbols.size() == 5);
  assert(G.nonterminals.size() == 3);
  assert(G.symbols["AUGMENTED_START"] == -1);
}


int main() {
  test_read1();
  test_read2();
  test_read3();
  test_bad_nonterminal();
  test_missing_productions();
  test_invalid_production();
  test_first();
  test_augmentStart();
}
