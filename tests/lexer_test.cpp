

#include "../lexer.hpp"
#include "../token.hpp"
#include <sstream>
#include <cassert>

void test_one() {
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

void test_two() {
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



int main() {
  test_one();
  test_two();
  test_three();
}
