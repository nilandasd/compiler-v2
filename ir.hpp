// ir.hpp

#pragma once

#include <utility>
#include <iostream>
#include <string>
#include <unordered_map>

#define LABEL 0
#define JUMP 1
#define EXPR 2
#define CONJ 3
#define ASG 4

#define ID_VAL 0
#define TEMP_VAL 1
#define INT_VAL 2

#define INT_TYPE 0 
#define FLOAT_TYPE 1

using value = std::pair<int, int>;

extern std::unordered_map<std::string, int>  operators;

class Tac {
  public: 
    int type = 0;
    int lab = 0;
    int identifier = 0;
    int op = 0;
    int temp = 0;
    int id = 0;
    value v1;
    value v2;

    static Tac* label(int l);
    static Tac* jump(int l);
    static Tac* expr(int temp, int op, value val1, value val2); 
    static Tac* conj(int l, int temp); 
    static Tac* asg(int id, int temp); 

    void print();
};

