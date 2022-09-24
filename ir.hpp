// ir.hpp

#pragma once

using value = std::pair<int, int>;

class Stmt {
  int type = 0;
  int label = 0;
  int identifier = 0;
  int op = 0;
  bool jump = false;
  value v1 {0, 0};
  value v2 {0, 0};
  std::string genCode();
};

