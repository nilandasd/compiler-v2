

#include "../lexer.hpp"
#include "../token.hpp"
#include <sstream>
#include <cassert>

void test_analyze1() {
  std::stringstream ss;
  ss << "if else while func return var";

  Lexer lex(&ss);
  lex.analyze();

  Token* t1 = lex.getToken();
  Token* t2 = lex.getToken();
  Token* t3 = lex.getToken();
  Token* t4 = lex.getToken();
  Token* t5 = lex.getToken();
  Token* t6 = lex.getToken();
  Token* t7 = lex.getToken();

  assert(t1->id == IF);
  assert(t1->toString().compare("IF") == 0);
  assert(t2->id == ELSE);
  assert(t2->toString().compare("ELSE") == 0);
  assert(t3->id == WHILE);
  assert(t3->toString().compare("WHILE") == 0);
  assert(t4->id == FUNC);
  assert(t4->toString().compare("FUNC") == 0);
  assert(t5->id == RETURN);
  assert(t5->toString().compare("RETURN") == 0);
  assert(t6->id == VAR);
  assert(t6->toString().compare("VAR") == 0);
  assert(t7->id == END);
  assert(t7->toString().compare("$") == 0);
}

void test_analyze2() {
  std::stringstream ss;
  ss << "test t If elsE test";

  Lexer lex(&ss);
  lex.analyze();

  IdToken* t1 = (IdToken*)lex.getToken();
  IdToken* t2 = (IdToken*)lex.getToken();
  IdToken* t3 = (IdToken*)lex.getToken();
  IdToken* t4 = (IdToken*)lex.getToken();
  IdToken* t5 = (IdToken*)lex.getToken();
  IdToken* t6 = (IdToken*)lex.getToken();

  assert(t1->id == ID);
  assert(t1->attr.compare("test") == 0);
  assert(t2->id == ID);
  assert(t2->attr.compare("t") == 0);
  assert(t3->id == ID);
  assert(t3->attr.compare("If") == 0);
  assert(t4->id == ID);
  assert(t4->attr.compare("elsE") == 0);
  assert(t5->id == ID);
  assert(t5->attr.compare("test") == 0);
  assert(t6->id == END);
}

void test_analyze3() {
  std::stringstream ss;
  ss << "0 123 99999 1";

  Lexer lex(&ss);
  lex.analyze();

  NumToken* t1 = (NumToken*)lex.getToken();
  NumToken* t2 = (NumToken*)lex.getToken();
  NumToken* t3 = (NumToken*)lex.getToken();
  NumToken* t4 = (NumToken*)lex.getToken();
  NumToken* t5 = (NumToken*)lex.getToken();

  assert(t1->id == NUM);
  assert(t1->attr == 0);
  assert(t2->id == NUM);
  assert(t2->attr == 123);
  assert(t3->id == NUM);
  assert(t3->attr == 99999);
  assert(t4->id == NUM);
  assert(t4->attr == 1);
  assert(t5->id == END);
}

/*
void test_analyze4() {
  std::stringstream ss;
  ss << "99999999999";

  Lexer lex(&ss);
  lex.analyze();
  
  NumToken* t1 = (NumToken*)lex.getToken();

  assert(t1->id == NUM);
  assert(t1->attr == 0);
}*/

void test_analyze5() {
  std::stringstream ss;
  
  Lexer lex(&ss);

  Token* t = lex.getToken();

  assert(t == NULL);
}



int main() {
  test_analyze1();
  test_analyze2();
  test_analyze3();
  //test_analyze4();
  test_analyze5();
}
