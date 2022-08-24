//token.cpp

#include "token.hpp"
#include "util.cpp"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<int, string> specialTokens ({
  { EQ,  "==" },
  { NEQ, "!=" },
  { GTE, ">=" },
  { LTE, "<=" },
  { END, "$"  }
});

unordered_map<string, int> reservedWords ({
  { "if",     IF     },
  { "else",   ELSE   },
  { "while",  WHILE  },
  { "func",   FUNC   },
  { "var",    VAR    },
  { "return", RETURN }
});

Token::Token(int n): id(n) {}

string Token::toString() {
  if ( id < 0 ) {
    return specialTokens[id];    
  } else {
    return string(1, static_cast<char>(id));
  }
}

IdToken::IdToken(string s): Token(ID), attr(s), reservedWord(false) {
  if (reservedWords.find(s) != reservedWords.end()) {
    reservedWord = true;
    id = reservedWords[s];
  }
}

string IdToken::toString() {
  if ( reservedWord ) {
    return capitalizeString(attr);
  } else {
    return "ID";
  }
}

NumToken::NumToken(int x): Token(NUM), attr(x) {}

string NumToken::toString() {
  return "NUM";
}
