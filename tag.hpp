// tag.hpp

#pragma once
#include <string>
#include <unordered_map>

using namespace std;

//SPECIAL TOKEN IDS
#define ID   -1
#define NUM  -2
#define EQ   -3
#define NEQ  -4
#define GT   -5
#define GTE  -6
#define LT   -7
#define LTE  -8
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

class Tag {
  public:
    int id;
    virtual string toString();
};

class IdTag: public Tag {
  public:
    string attr;
    bool reservedWord;
    virtual string toString();
};

class NumTag: public Tag {
  public:
    int attr;
    virtual string toString();
};
