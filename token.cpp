//token.cpp

#include "token.hpp"
#include "util.hpp"
#include <iostream>
#include <string>
#include <unordered_map>


std::unordered_map<std::string, int> specialTokens ({
  { "==", EQ   },
  { "!=", NEQ  },
  { ">=", GTE  },
  { "<=", LTE  },
  { "||", OR   },
  { "&&", AND  },
  { "$" , END  }
});

std::unordered_map<std::string, int> reservedWords ({
  { "if",     IF     },
  { "else",   ELSE   },
  { "while",  WHILE  },
  { "func",   FUNC   },
  { "var",    VAR    },
  { "return", RETURN },
  { "int",    INT    },
  { "long",   LONG   }
});

std::string Token::toString() {
  if ( id < 0 ) {
    for (auto& it: specialTokens) {
      if ( it.second == id )
        return it.first;    
    }
  }
  
  return std::string(1, static_cast<char>(id));
}

IdToken::IdToken(std::string s): Token(ID), attr(s) {
  if (reservedWords.find(s) != reservedWords.end()) {
    id = reservedWords[s];
  }
}

std::string IdToken::toString() {
  if ( id != ID) {
    return capitalize(attr);
  } else {
    return "ID";
  }
}

std::string NumToken::toString() {
  return "NUM";
}
