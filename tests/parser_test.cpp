// slr_test.cpp


#include "../parser.hpp"
#include "../lexer.hpp"
#include <fstream>
#include <cassert>

void test_SLR() {
  std::ifstream file( "./tests/grammars/g1.txt");
  if (!file) assert(false);
  std::stringstream ss;
  ss << file.rdbuf();
  file.close();
  Grammar G(&ss);  
  G.read();
  G.augmentStart();

  SLR slr(G);
  slr.init();
  // slr.print();

  assert(slr.states.size() == 12);

  // state 0
  State s0(0);
  std::vector<int> v0{CURSOR, G.serialize("E")};
  Item *i0 = new Item(AUGMENTED_START, v0, DNE);
  s0.items.push_back(i0);
  assert(*(slr.states[0]) == s0);
  assert(slr.states[0]->moves.size() == 5);
  assert(slr.states[0]->moves[G.serialize("E")] == slr.states[1] );
  assert(slr.states[0]->moves[G.serialize("T")] == slr.states[2] );
  assert(slr.states[0]->moves[G.serialize("ID")] == slr.states[5]);
  assert(slr.states[0]->moves[G.serialize("(")] == slr.states[4] );
  assert(slr.states[0]->moves[G.serialize("F")] == slr.states[3] );

  // state 1
  State s1(1);
  std::vector<int> v1{G.serialize("E"), CURSOR};
  std::vector<int> v2{G.serialize("E"), CURSOR, G.serialize("+"), G.serialize("T")};
  Item *i1 = new Item(AUGMENTED_START, v1, DNE);
  Item *i2 = new Item(G.serialize("E"), v2, DNE);
  s1.items.push_back(i1);
  s1.items.push_back(i2);
  assert(*(slr.states[1]) == s1);
  assert(slr.states[1]->moves.size() == 1);
  assert(slr.states[1]->moves[G.serialize("+")] == slr.states[6] );
  //assert(slr.states[0]->moves[ACCEPT] == ACCEPT_STATE );

  // state 2
  State s2(2);
  std::vector<int> v3{G.serialize("T"), CURSOR};
  std::vector<int> v4{G.serialize("T"), CURSOR, G.serialize("*"), G.serialize("F")};
  Item *i3 = new Item(G.serialize("E"), v3, DNE);
  Item *i4 = new Item(G.serialize("T"), v4, DNE);
  s2.items.push_back(i3);
  s2.items.push_back(i4);
  assert(*(slr.states[2]) == s2);
  assert(slr.states[2]->moves.size() == 1);
  assert(slr.states[2]->moves[G.serialize("*")] == slr.states[7] );

  // state 3
  State s3(3);
  std::vector<int> v5{G.serialize("F"), CURSOR};
  Item *i5 = new Item(G.serialize("T"), v5, DNE);
  s3.items.push_back(i5);
  assert(*(slr.states[3]) == s3);
  assert(slr.states[3]->moves.size() == 0);

  // state 4
  State s4(4);
  std::vector<int> v6{G.serialize("("), CURSOR, G.serialize("E"), G.serialize(")")};
  Item *i6 = new Item(G.serialize("F"), v6, DNE);
  s4.items.push_back(i6);
  assert(*(slr.states[4]) == s4);
  assert(slr.states[4]->moves.size() == 5);
  assert(slr.states[4]->moves[G.serialize("E")] == slr.states[8] );
  assert(slr.states[4]->moves[G.serialize("T")] == slr.states[2] );
  assert(slr.states[4]->moves[G.serialize("ID")] == slr.states[5]);
  assert(slr.states[4]->moves[G.serialize("(")] == slr.states[4] );
  assert(slr.states[4]->moves[G.serialize("F")] == slr.states[3] );

  // state 5
  State s5(5);
  std::vector<int> v7{G.serialize("ID"), CURSOR};
  Item *i7 = new Item(G.serialize("F"), v7, DNE);
  s5.items.push_back(i7);
  assert(*(slr.states[5]) == s5);
  assert(slr.states[5]->moves.size() == 0);

  // state 6
  State s6(6);
  std::vector<int> v8{G.serialize("E"), G.serialize("+"), CURSOR, G.serialize("T")};
  Item *i8 = new Item(G.serialize("E"), v8, DNE);
  s6.items.push_back(i8);
  assert(*(slr.states[6]) == s6);
  assert(slr.states[6]->moves.size() == 4);
  assert(slr.states[6]->moves[G.serialize("T")] == slr.states[9] );
  assert(slr.states[6]->moves[G.serialize("ID")] == slr.states[5]);
  assert(slr.states[6]->moves[G.serialize("(")] == slr.states[4] );
  assert(slr.states[6]->moves[G.serialize("F")] == slr.states[3] );

  // state 7
  State s7(7);
  std::vector<int> v9{G.serialize("T"), G.serialize("*"), CURSOR, G.serialize("F")};
  Item *i9 = new Item(G.serialize("T"), v9, DNE);
  s7.items.push_back(i9);
  assert(*(slr.states[7]) == s7);
  assert(slr.states[7]->moves.size() == 3);
  assert(slr.states[7]->moves[G.serialize("F")] == slr.states[10] );
  assert(slr.states[7]->moves[G.serialize("ID")] == slr.states[5]);
  assert(slr.states[7]->moves[G.serialize("(")] == slr.states[4] );

  // state 8
  State s8(8);
  std::vector<int> v10{G.serialize("E"), CURSOR, G.serialize("+"), G.serialize("T")};
  std::vector<int> v11{G.serialize("("), G.serialize("E"), CURSOR, G.serialize(")")};
  Item *i10 = new Item(G.serialize("E"), v10, DNE);
  Item *i11 = new Item(G.serialize("F"), v11, DNE);
  s8.items.push_back(i10);
  s8.items.push_back(i11);
  assert(*(slr.states[8]) == s8);
  assert(slr.states[8]->moves.size() == 2);
  assert(slr.states[8]->moves[G.serialize(")")] == slr.states[11] );
  assert(slr.states[8]->moves[G.serialize("+")] == slr.states[6] );

  // state 9
  State s9(9);
  std::vector<int> v12{G.serialize("E"), G.serialize("+"), G.serialize("T"), CURSOR};
  std::vector<int> v13{G.serialize("T"), CURSOR, G.serialize("*"), G.serialize("F")};
  Item *i12 = new Item(G.serialize("E"), v12, DNE);
  Item *i13 = new Item(G.serialize("T"), v13, DNE);
  s9.items.push_back(i12);
  s9.items.push_back(i13);
  assert(*(slr.states[9]) == s9);
  assert(slr.states[9]->moves.size() == 1);
  assert(slr.states[9]->moves[G.serialize("*")] == slr.states[7] );

  // state 10
  State s10(10);
  std::vector<int> v14{G.serialize("T"), G.serialize("*"), G.serialize("F"), CURSOR};
  Item *i14 = new Item(G.serialize("T"), v14, DNE);
  s10.items.push_back(i14);
  assert(*(slr.states[10]) == s10);
  assert(slr.states[10]->moves.size() == 0);

  // state 11
  State s11(11);
  std::vector<int> v15{G.serialize("("), G.serialize("E"), G.serialize(")"), CURSOR};
  Item *i15 = new Item(G.serialize("F"), v15, DNE);
  s11.items.push_back(i15);
  assert(*(slr.states[11]) == s11);
  assert(slr.states[11]->moves.size() == 0);

  for (auto state : slr.states) {
    for (auto item : state.second->items) {
      assert(item->lookahead == DNE);
    }
  }
}

void test_LALR_automaton() {
  std::ifstream file( "./tests/grammars/g2.txt");
  if (!file) assert(false);
  std::stringstream ss;
  ss << file.rdbuf();
  file.close();
  Grammar G(&ss);  
  G.read();
  G.augmentStart();

  LALR lalr(G);
  lalr.init();
  assert(lalr.states.size() == 10);

  // state 0
  State s0(0);
  std::vector<int> v0{CURSOR, G.serialize("S")};
  Item *i0 = new Item(AUGMENTED_START, v0, ACCEPT);
  s0.items.push_back(i0);
  assert(*(lalr.states[0]) == s0);

  // state 1
  State s1(1);
  std::vector<int> v1{G.serialize("S"), CURSOR};
  Item *i1 = new Item(AUGMENTED_START, v1, ACCEPT);
  s1.items.push_back(i1);
  assert(*(lalr.states[1]) == s1);

  // state 2
  State s2(2);
  std::vector<int> v2{G.serialize("L"), CURSOR, G.serialize("="), G.serialize("R")};
  std::vector<int> v3{G.serialize("L"), CURSOR};
  Item *i2 = new Item(G.serialize("S"), v2, ACCEPT);
  Item *i3 = new Item(G.serialize("R"), v3, ACCEPT);
  s2.items.push_back(i2);
  s2.items.push_back(i3);
  assert(*(lalr.states[2]) == s2);

  // state 3
  State s3(3);
  std::vector<int> v4{G.serialize("R"), CURSOR};
  Item *i4 = new Item(G.serialize("S"), v4, ACCEPT);
  s3.items.push_back(i4);
  assert(*(lalr.states[3]) == s3);

  // state 4
  State s4(4);
  std::vector<int> v5{G.serialize("*"), CURSOR, G.serialize("R")};
  std::vector<int> v6{G.serialize("*"), CURSOR, G.serialize("R")};
  Item *i5 = new Item(G.serialize("L"), v5, ACCEPT);
  Item *i6 = new Item(G.serialize("L"), v6, G.serialize("="));
  s4.items.push_back(i5);
  s4.items.push_back(i6);
  assert(*(lalr.states[4]) == s4);

  // state 5
  State s5(5);
  std::vector<int> v7{G.serialize("ID"), CURSOR};
  std::vector<int> v8{G.serialize("ID"), CURSOR};
  Item *i7 = new Item(G.serialize("L"), v7, ACCEPT);
  Item *i8 = new Item(G.serialize("L"), v8, G.serialize("="));
  s5.items.push_back(i7);
  s5.items.push_back(i8);
  assert(*(lalr.states[5]) == s5);

  // state 6
  State s6(6);
  std::vector<int> v9{G.serialize("L"), G.serialize("="), CURSOR, G.serialize("R")};
  Item *i9 = new Item(G.serialize("S"), v9, ACCEPT);
  s6.items.push_back(i9);
  assert(*(lalr.states[6]) == s6);

  // state 7
  State s7(7);
  std::vector<int> v10{G.serialize("*"), G.serialize("R"), CURSOR};
  std::vector<int> v11{G.serialize("*"), G.serialize("R"), CURSOR};
  Item *i10 = new Item(G.serialize("L"), v10, ACCEPT);
  Item *i11 = new Item(G.serialize("L"), v11, G.serialize("="));
  s7.items.push_back(i10);
  s7.items.push_back(i11);
  assert(*(lalr.states[7]) == s7);

  // state 8
  State s8(8);
  std::vector<int> v12{G.serialize("L"), CURSOR};
  std::vector<int> v13{G.serialize("L"), CURSOR};
  Item *i12 = new Item(G.serialize("R"), v12, ACCEPT);
  Item *i13 = new Item(G.serialize("R"), v13, G.serialize("="));
  s8.items.push_back(i12);
  s8.items.push_back(i13);
  assert(*(lalr.states[8]) == s8);

  // state 9
  State s9(9);
  std::vector<int> v14{G.serialize("L"), G.serialize("="), G.serialize("R"), CURSOR};
  Item *i14 = new Item(G.serialize("S"), v14, ACCEPT);
  s9.items.push_back(i14);
  assert(*(lalr.states[9]) == s9);
}

void test_LALR_init() {
  std::ifstream file( "./grammar.txt");
  if (!file) assert(false);
  std::stringstream ss;
  ss << file.rdbuf();
  file.close();
  Grammar G(&ss);  
  G.read();
  G.augmentStart();

  LALR lalr(G);
  lalr.init();
}

void test_parse1() {
  std::ifstream file( "./tests/grammars/g2.txt");
  if (!file) assert(false);
  std::stringstream ss;
  ss << file.rdbuf();
  file.close();
  Grammar G(&ss);  
  G.read();
  G.augmentStart();

  LALR lalr(G);
  lalr.init();

  std::ifstream file2( "./tests/programs/g2/one.txt");
  std::stringstream ss2;
  ss2 << file2.rdbuf();
  file2.close();
  Lexer lexer(&ss2);
  lexer.analyze();
  std::vector<int> symbols;
  while(true) {
    Token* token = lexer.getToken();
    if (token == NULL) break;
    symbols.push_back(G.tokenSymbol(token));
  }

  lalr.parse(symbols);
}

void test_parse2() {
  std::ifstream file( "./tests/grammars/g2.txt");
  if (!file) assert(false);
  std::stringstream ss;
  ss << file.rdbuf();
  file.close();
  Grammar G(&ss);  
  G.read();
  G.augmentStart();

  LALR lalr(G);
  lalr.init();

  std::ifstream file2( "./tests/programs/g2/two.txt");
  std::stringstream ss2;
  ss2 << file2.rdbuf();
  file2.close();
  Lexer lexer(&ss2);
  lexer.analyze();
  std::vector<int> symbols;
  while(true) {
    Token* token = lexer.getToken();
    if (token == NULL) break;
    symbols.push_back(G.tokenSymbol(token));
  }

  lalr.parse(symbols);
}

void test_parse3() {
  std::ifstream file( "./tests/grammars/g2.txt");
  if (!file) assert(false);
  std::stringstream ss;
  ss << file.rdbuf();
  file.close();
  Grammar G(&ss);  
  G.read();
  G.augmentStart();

  LALR lalr(G);
  lalr.init();

  std::ifstream file2( "./tests/programs/g2/three.txt");
  std::stringstream ss2;
  ss2 << file2.rdbuf();
  file2.close();
  Lexer lexer(&ss2);
  lexer.analyze();
  std::vector<int> symbols;
  while(true) {
    Token* token = lexer.getToken();
    if (token == NULL) break;
    symbols.push_back(G.tokenSymbol(token));
  }

  try {
    lalr.parse(symbols);
    assert(false);
  } catch(std::runtime_error &e) {
    assert(true);
  }
}

void test_parse4() {
  std::ifstream file( "./tests/grammars/g1.txt");
  if (!file) assert(false);
  std::stringstream ss;
  ss << file.rdbuf();
  file.close();
  Grammar G(&ss);  
  G.read();
  G.augmentStart();

  LALR lalr(G);
  lalr.init();

  std::ifstream file2( "./tests/programs/g1/one.txt");
  std::stringstream ss2;
  ss2 << file2.rdbuf();
  file2.close();
  Lexer lexer(&ss2);
  lexer.analyze();
  std::vector<int> symbols;
  while(true) {
    Token* token = lexer.getToken();
    if (token == NULL) break;
    symbols.push_back(G.tokenSymbol(token));
  }

  lalr.parse(symbols);
}

void test_parse5() {
  std::ifstream file( "./tests/grammars/g1.txt");
  if (!file) assert(false);
  std::stringstream ss;
  ss << file.rdbuf();
  file.close();
  Grammar G(&ss);  
  G.read();
  G.augmentStart();

  LALR lalr(G);
  lalr.init();

  std::ifstream file2( "./tests/programs/g1/two.txt");
  std::stringstream ss2;
  ss2 << file2.rdbuf();
  file2.close();
  Lexer lexer(&ss2);
  lexer.analyze();
  std::vector<int> symbols;
  while(true) {
    Token* token = lexer.getToken();
    if (token == NULL) break;
    symbols.push_back(G.tokenSymbol(token));
  }

  try {
    lalr.parse(symbols);
    assert(false);     
  } catch(std::runtime_error &e) {
    assert(true);
  }
}

int main() {
  test_SLR();
  test_LALR_automaton();
  test_LALR_init();
  test_parse1();
  test_parse2();
  test_parse3();
  test_parse4();
  test_parse5();
}
