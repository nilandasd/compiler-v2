// lexer.cpp

#include "lexer.hpp"

void Lexer::analyze() {
  char c;

  while(ss->get(c)) {
    if ( isspace(c) ) continue;

    if ( isalpha(c) ) {
      readId(c);
      continue;
    }

    if ( isdigit(c) ) {
      readNum(c);
      continue;
    }

    if ( checkPeek(c) ) {
      std::string s;
      s += c;
      s += ss->peek();
      if ( specialTokens.find(s) == specialTokens.end() ) return;
      Token* t = new Token(specialTokens[s]);
      tokens.push_back(t);
      continue;
    }

    Token* t = new Token((int)c);
    tokens.push_back(t);
  }

  Token* t = new Token(END);
  tokens.push_back(t);
}

Token* Lexer::getToken() {
  if (tokens.empty()) return NULL;

  Token* result = tokens.front();
  tokens.pop_front();

  return result;
}

void Lexer::readNum(char c) {
  std::string x(1, c);

  while ( isdigit(ss->peek()) ) {
    ss->get(c);

    x += c;
  }

  NumToken* t = new NumToken(stoi(x));
  tokens.push_back(t);
}

bool Lexer::checkPeek(char c) {
  if (c == '=' || c == '!' || c == '<' || c == '>' || c == '&' || c == '|') return true;
  return false;
}

void Lexer::readId(char c) {
  std::string s(1, c);

  while ( isalpha(ss->peek()) ) {
    ss->get(c);

    s += c;
  }

  IdToken* t = new IdToken(s);
  tokens.push_back(t);
}

