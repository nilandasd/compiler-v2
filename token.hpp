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
#define END  -7

//RESERVED WORDS
#define IF     -8
#define ELSE   -9
#define WHILE  -10
#define FUNC   -11
#define RETURN -12
#define VAR    -13
#define INT    -14
#define LONG   -15

/*
All other tokens that are neither of type ID, NUM, Reservered Words, 
or two character relational operators, will be of base type Token, and 
have an id equal to that of the ascii number for the character 
it represents.
*/

class Token {
  public:
    int id;
    int attr = NULL;

    Token(int n);
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

    NumToken(int x);
    virtual std::string toString();
};
