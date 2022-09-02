//  main.cpp

#include "token.hpp"
#include "lexer.hpp"
#include "grammar.hpp"

int main() {
  std::stringstream ss;
  ss << "testng 1 2 3 ! :)";
  Lexer lex(&ss);
  lex.analyze();

  Token* t = lex.getToken();

  IdToken* i = (IdToken*)t;
  std::cout << t->toString() << std::endl;
  std::cout << i->attr << std::endl;
  
  std::stringstream sss;
  Grammar grammar(&sss);

  sss << "START\n\t| this is a test\n\t| did it work?";
  grammar.read();

  return 0;
}
