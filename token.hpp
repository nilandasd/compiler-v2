// token.hpp

#pragma once

#include <string>
#include <unordered_map>

//TOKEN IDS
#define ID   -1
#define NUM  -2
#define EQ   -3
#define NEQ  -4
#define GTE  -5
#define LTE  -6
#define AND  -7
#define OR   -8
#define END  -9

//RESERVED WORDS
#define IF     -10
#define ELSE   -11
#define WHILE  -12
#define FUNC   -13
#define RETURN -14
#define VAR    -15
#define INT    -16
#define LONG   -17

/*
All other tokens that are neither of type ID, NUM, Reservered Words, 
or two character relational operators, will be of base type Token, and 
have an id equal to that of the ascii number for the character 
it represents.
*/

extern std::unordered_map<std::string, int> specialTokens;

class Token {
  public:
    int id;

    Token(int n): id(n) {}
    virtual std::string toString();
};

class IdToken: public Token {
  public:
    std::string attr;
    bool reservedWord;

    IdToken(std::string s);
    virtual std::string toString();
};

class NumToken: public Token {
  public:
    int attr;

    NumToken(int x): Token(NUM), attr(x) {};
    virtual std::string toString();
};
