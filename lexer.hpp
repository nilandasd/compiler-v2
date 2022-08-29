// lexer.hpp

#pragma once

#include "token.hpp"
#include <deque>
#include <sstream>

class Lexer {
  public:
    Lexer(std::stringstream* s): ss{s} {};
    void analyze();
    Token* getToken();

  private:
    std::stringstream* ss;
    std::deque<Token*> tokens;
    void readId(char c); 
    void readNum(char c);
    bool checkPeek(char c); 
};
