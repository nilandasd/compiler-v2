//token.cpp

#include "token.hpp"
#include "util.cpp"
#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<int, std::string> specialTokens ({
  { EQ,  "==" },
  { NEQ, "!=" },
  { GTE, ">=" },
  { LTE, "<=" },
  { END, "$"  }
});

std::unordered_map<std::string, int> reservedWords ({
  { "if",     IF     },
  { "else",   ELSE   },
  { "while",  WHILE  },
  { "func",   FUNC   },
  { "var",    VAR    },
  { "return", RETURN }
});

Token::Token(int n): id(n) {}

std::string Token::toString() {
  if ( id < 0 ) {
    return specialTokens[id];    
  } else {
    return std::string(1, static_cast<char>(id));
  }
}

IdToken::IdToken(std::string s): Token(ID), attr(s) {
  if (reservedWords.find(s) != reservedWords.end()) {
    id = reservedWords[s];
  }
}

std::string IdToken::toString() {
  if ( id != ID) {
    return capitalizeString(attr);
  } else {
    return "ID";
  }
}

NumToken::NumToken(int x): Token(NUM), attr(x) {}

std::string NumToken::toString() {
  return "NUM";
}
