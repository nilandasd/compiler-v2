//  main.cpp

#include <iostream>
#include "token.hpp"
#include "lexer.hpp"
#include <iostream>
#include <sstream>

int main() {
  std::stringstream ss;
  ss << "testng 1 2 3 ! :)";
  Lexer lex(&ss);
  lex.analyze();

  Token* t = lex.getToken();

  IdToken* i = (IdToken*)t;
  std::cout << t->toString() << std::endl;
  std::cout << i->attr << std::endl;
 
  return 0;
}
