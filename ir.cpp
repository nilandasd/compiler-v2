// ir.cpp

#include "ir.hpp"

std::unordered_map<std::string, int>  operators ({
  {"&&", 0},
  {"||", 1},
  {"==", 2},
  {"!=", 3},
  {">=", 4},
  {">",  5},
  {"<=", 6},
  {"<",  7},
  {"*",  8},
  {"/",  9},
  {"+",  10},
  {"-",  11},
});

Tac* Tac::label(int l) {
  Tac* tac = new Tac();
  tac->type = LABEL;
  tac->lab = l;
  return tac;
}

Tac* Tac::jump(int l) {
  Tac* tac = new Tac();
  tac->type = JUMP;
  tac->lab = l;
  return tac;
}

Tac* Tac::expr(int t, int op, value val1, value val2) {
  Tac* tac = new Tac();
  tac->type = EXPR;
  tac->op = op;
  tac->v1 = val1;
  tac->v2 = val2;
  tac->temp = t;
}

Tac* Tac::conj(int l, int t) {
  Tac* tac = new Tac();
  tac->type = CONJ;
  tac->temp = t;
  tac->lab = l;
}

Tac* Tac::asg(int i, int t) {
  Tac* tac = new Tac();
  tac->type = ASG;
  tac->temp = t;
  tac->id = i;
}

std::string valueToString(value v) {
  int type = v.first;

  if (type == ID_VAL) {
    return "i" + std::to_string(v.second);
  } else if (type == TEMP_VAL) {
    return "t" + std::to_string(v.second);
  } else {
    return std::to_string(v.second);
  }
}

std::string opString(int op) {
  for (auto p: operators) {
    if (p.second == op) return p.first;
  }
}

void Tac::print() {
  if (type == EXPR) {
    std::cout << "t" << temp << " = " << valueToString(v1) << " " << opString(op) << " " << valueToString(v2) << std::endl;
  } else if (type == LABEL) {
    std::cout << "LABEL " << lab << std::endl;
  } else if (type == JUMP) {
    std::cout << "JUMP " << lab << std::endl;
  } else if (type == CONJ) {
    std::cout << "IF t" << temp << " == 0 JUMP " << lab << std::endl;
  } else if (type == ASG) {
    std::cout << "i" << id << " = t" << temp << std::endl;
  }
}
